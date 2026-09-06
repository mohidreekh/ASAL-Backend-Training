#include "TCPServer.hpp"
#include "ClientSession.hpp"
#include "Chat.hpp"
#include<iostream>

using namespace boost::asio;
using namespace boost;

TCPServer::TCPServer(io_context &io, unsigned short port) 
	: _io(io), _acceptor(io, ip::tcp::endpoint(ip::tcp::v4(), port)) {}

void TCPServer::start() 
{
	std::cout << "Server Started at port" << _acceptor.local_endpoint().port() << std::endl;

	_acceptClient();
}

void TCPServer::stop()
{
    _stopped = true;

    boost::system::error_code ec;
    _acceptor.close(ec);

    if (ec)
    {
        std::cout
            << "Server shutdown error: "
            << ec.message()
            << '\n';
    }
}

void TCPServer::_acceptClient() 
{
	_acceptor.async_accept([this](system::error_code ec, ip::tcp::socket socket) {
        if (!ec)
        {
            std::cout << "Thread: " << std::this_thread::get_id() << '\n';

            std::this_thread::sleep_for(std::chrono::seconds(2));

            // shared_ptr keeps the Session alive after the handler ends.
            // Asynchronous operations may still be running, so the Session
            // must not be destroyed until all shared_ptr references are gone.
            auto client = std::make_shared<ClientSession>(std::move(socket));

            _chat.addClient(client);
      
            client->start();

        }
        else
        {
            if (!_stopped)
            {
                std::cout << "Accept error: " << ec.message() << '\n';
            }
        }

        if (!_stopped) 
        {
            _acceptClient();
        }
	});
}
