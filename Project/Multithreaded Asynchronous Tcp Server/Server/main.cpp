#include<iostream>
#include"TCPServer.hpp"

int main() {
	boost::asio::io_context io;

	TCPServer server(io, 8080);

	server.start();

	io.run();
}