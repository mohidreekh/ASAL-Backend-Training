#include "TCPServer.hpp"
#include "ClientSession.hpp"
#include "ClientManager.hpp"
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

void TCPServer::_acceptClient() 
{
	_acceptor.async_accept([this](system::error_code ec, ip::tcp::socket socket) {
        if (!ec)
        {
            // shared_ptr keeps the Session alive after the handler ends.
            // Asynchronous operations may still be running, so the Session
            // must not be destroyed until all shared_ptr references are gone.
            auto session = std::make_shared<ClientSession>(std::move(socket));

            _clientManager.add(session);

            std::cout << "Client connected. Total Clients : " << _clientManager.size() << std::endl;

            session->setOnDisconnect(
                [this, session]()
                {
                    _clientManager.remove(session);

                    std::cout
                        << "Client removed\n"
                        << "Clients: "
                        << _clientManager.size()
                        << '\n';
                });

            session->setOnMessage(
                [this, session](const std::string& message)
                {
                    std::string fullMessage = session->getUsername() + ": " + message;

                    _clientManager.broadcast(fullMessage, session);
                });

            session->start();
        }
        else
        {
            std::cout << "Accept error: "
                << ec.message()
                << '\n';
        }

        _acceptClient();

	});
}
