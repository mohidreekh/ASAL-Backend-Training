#pragma once

#include <boost/asio/io_context.hpp>

#include <cstddef>
#include <thread>
#include <vector>

class IOThreadPool
{
private:
    boost::asio::io_context& _io;
    std::vector<std::thread> _threads;

    // Keeps the io_context running even when there are no pending asynchronous operations.
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _workGuard;

public:
    IOThreadPool(boost::asio::io_context& io, std::size_t threadCount);

    void join();
    void stop();

private:
    void _start();

};