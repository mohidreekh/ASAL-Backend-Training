#include "IOThreadPool.hpp"

#include <stdexcept>

IOThreadPool::IOThreadPool(boost::asio::io_context& io, std::size_t threadCount)
    : _io(io), _workGuard(boost::asio::make_work_guard(_io))
{
    if (threadCount == 0)
    {
        throw std::invalid_argument("Thread count must be greater than zero");
    }

    _threads.reserve(threadCount);

    _start();
}

void IOThreadPool::_start()
{
    for (std::size_t i = 0; i < _threads.capacity(); ++i)
    {
        _threads.emplace_back([this]()
            {
                _io.run();
            });
    }
}

void IOThreadPool::join()
{
    for (auto& thread : _threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}

void IOThreadPool::stop()
{
    _workGuard.reset();
}