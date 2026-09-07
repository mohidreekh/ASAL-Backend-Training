#include "ClientSession.hpp"
#include"MessageFramer.hpp"
#include<iostream>

using namespace boost;
using namespace boost::asio;


ClientSession::ClientSession(ip::tcp::socket socket) : _socket(std::move(socket)), _vBuffer(1024), _strand(_socket.get_executor()) {}

void ClientSession::start()
{
    std::cout << "Client session started: " << _socket.remote_endpoint() << '\n';

    send("Enter Username :");

    _read();
}

void ClientSession::_send(std::vector<uint8_t> data) {
    bool writeInProgress = !_writeQueue.empty();

    _writeQueue.push_back(std::move(data));

    //Check if there is no write in progress
    if (!writeInProgress)
    {
        _write();
    }
}

void ClientSession::_write() {

    auto self = shared_from_this();

    async_write(_socket, buffer(_writeQueue.front()),
        boost::asio::bind_executor(_strand, [self](system::error_code ec, size_t bytes) {
            if (!ec)
            {
                std::cout << "Sent " << bytes << " bytes\n";
                self->_writeQueue.pop_front();

                if (!self->_writeQueue.empty())
                {
                    self->_write();
                }
            }
            else
            {
                std::cout << "Write error: " << ec.message() << '\n';
                self->disconnect();
            }
        }));

}

void ClientSession::_read() {

    auto self = shared_from_this();

    _socket.async_read_some(buffer(_vBuffer), 
        boost::asio::bind_executor(_strand, [self](system::error_code ec, size_t length) {
            if (ec)
            {
                if (ec == boost::asio::error::eof)
                {
                    std::cout << "Client disconnected normally.\n";
                }
                else if (ec == boost::asio::error::connection_reset)
                {
                    std::cout << "Client connection reset.\n";
                }
                else
                {
                    std::cout << "Read error: " << ec.message() << '\n';
                }

                self->disconnect();

                return;
            }

            std::cout << "Received " << length << " bytes \n";

            self->incomingBuffer.insert(self->incomingBuffer.end(), self->_vBuffer.begin(), self->_vBuffer.begin() + length);

            std::vector<std::string> messages;

            try {
                MessageFramer::extract(self->incomingBuffer, messages);
            }
            catch (const std::exception& e)
            {
                std::cout << "Framing error: " << e.what() << std::endl;
                self->disconnect();
                return;
            }

            for (const auto& message : messages)
            {
                self->_handleMessage(message);
            }

            self->_read();
            }));
}

const bool ClientSession::hasUserName()
{
    if (_username == "" || _username == "Anonymous")
    {
        return false;
    }
    return true;
}


void ClientSession::_handleMessage(const std::string& message)
{
    if (_onMessage)
    {
        _onMessage(message);
    }
}


void ClientSession::setOnDisconnect(std::function<void()> callback)
{
    _onDisconnect = std::move(callback);
}

void ClientSession::disconnect()
{
    if (_disconnected)
    {
        return;
    }
    _disconnected = true;

    boost::system::error_code ec;
    _socket.shutdown(ip::tcp::socket::shutdown_both, ec);
    _socket.close(ec);

    if (_onDisconnect) 
    {
        _onDisconnect();
    }
}

void ClientSession::send(const std::string& message)
{
    auto framed = MessageFramer::frame(message);
    auto self = shared_from_this();
    boost::asio::post(_strand,
        [self, data = std::move(framed)]() mutable
        {
            self->_send(std::move(data));
        });
}

void ClientSession::setOnMessage(std::function<void(const std::string&)> callback)
{
    _onMessage = std::move(callback);
}

void ClientSession::setUsername(const std::string& username)
{
    _username = username;
}

const std::string& ClientSession::getUsername() const
{
    return _username;
}

/*
    Boost.Asio Multithreading Functions:

    strand
    - Ensures handlers using the same strand are not executed concurrently.

    bind_executor()
    - Binds an async handler to a specific executor/strand.
    - Makes the handler execute through that strand.

    post()
    - Schedules a function to be executed by the given executor/strand.
    - Useful when a function may be called from another thread.

    In this project:
    - strand protects each ClientSession from concurrent handlers.
    - bind_executor() is used with async read/write handlers.
    - post() is used by send() to safely modify the write queue.
*/