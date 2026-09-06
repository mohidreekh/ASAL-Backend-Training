#include<iostream>
#include<thread>

#include"TCPServer.hpp"
#include "IOThreadPool.hpp"

const short int NUMBER_OF_THREADS = 4;

int main() {
    boost::asio::io_context io;

    TCPServer server(io, 8080);
    server.start();

    IOThreadPool pool(io, 4);
    pool.join();
}