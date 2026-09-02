#pragma once
#include <boost/asio.hpp>
#include "ClientManager.hpp"

using namespace boost::asio;

class TCPServer
{
private:
    io_context& _io;
    ip::tcp::acceptor _acceptor;
    ClientManager _clientManager;

public:
    TCPServer(io_context& _io, unsigned short port);

    void start();

private:
    void _acceptClient();
};
