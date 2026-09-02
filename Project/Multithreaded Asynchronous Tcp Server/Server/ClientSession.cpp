#include "ClientSession.hpp"
#include"MessageFramer.hpp"
#include<iostream>

using namespace boost;
using namespace boost::asio;


ClientSession::ClientSession(ip::tcp::socket socket) : _socket(std::move(socket)), _vBuffer(1024) {}

void ClientSession::start()
{
    std::cout
        << "Client session started: "
        << _socket.remote_endpoint()
        << '\n';

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
        [self](system::error_code ec, size_t bytes) {
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
                boost::system::error_code closeEc;
                self->_socket.close(closeEc);
            }
        });

}

void ClientSession::_read() {

    auto self = shared_from_this();

    _socket.async_read_some(buffer(_vBuffer), [self](system::error_code ec, size_t length) {
        if (ec)
        {
            std::cout << "Client Disconnected\n" << ec.message();

            if (self->_onDisconnect)
            {
                self->_onDisconnect();
            }

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
            return;
        }

        for (const auto& message : messages)
        {
            self->_handleMessage(message);
        }

        self->_read();        
    });
}

void ClientSession::_handleMessage(const std::string& message)
{
    if (message.rfind("/name ", 0) == 0)
    {
        std::string username = message.substr(6);

        if (!username.empty())
        {
            setUsername(username);

            std::cout << "Username changed to: " << _username << '\n';
        }

        return;
    }

    if (_onMessage)
    {
        _onMessage(message);
    }
}


void ClientSession::setOnDisconnect(std::function<void()> callback)
{
    _onDisconnect = std::move(callback);
}

void ClientSession::send(const std::string& message)
{
    auto framed = MessageFramer::frame(message);

    _send(std::move(framed));
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