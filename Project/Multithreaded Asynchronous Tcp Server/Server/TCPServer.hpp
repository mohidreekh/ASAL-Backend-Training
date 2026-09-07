#pragma once
#include <boost/asio.hpp>
#include"Chat.hpp"
using namespace boost::asio;

class TCPServer
{
private:
    io_context& _io;
    ip::tcp::acceptor _acceptor;
    Chat _chat;

    bool _stopped = false;

public:
    TCPServer(io_context& _io, unsigned short port);

    void start();

    void stop();

private:
    void _acceptClient();
};
