#include <boost/test/unit_test.hpp>

#include "IOThreadPool.hpp"

#include <boost/asio.hpp>
#include <chrono>
#include <thread>

BOOST_AUTO_TEST_SUITE(IOThreadPoolTests)

BOOST_AUTO_TEST_CASE(zero_threads_throws)
{
    boost::asio::io_context io;

    BOOST_CHECK_THROW(IOThreadPool(io, 0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(threads_run_io_context)
{
    boost::asio::io_context io;
    IOThreadPool pool(io, 2);

    bool executed = false;

    boost::asio::post(io, [&executed]()
        {
            executed = true;
        });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    BOOST_CHECK(executed);

    pool.stop();
    pool.join();
}

BOOST_AUTO_TEST_CASE(stop_allows_io_context_to_finish)
{
    boost::asio::io_context io;
    IOThreadPool pool(io, 2);

    pool.stop();
    pool.join();
}

BOOST_AUTO_TEST_SUITE_END()
