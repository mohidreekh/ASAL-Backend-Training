#include <boost/test/unit_test.hpp>

#include "IOThreadPool.hpp"
#include "TCPServer.hpp"

#include <boost/asio.hpp>

BOOST_AUTO_TEST_SUITE(TCPServerTests)

BOOST_AUTO_TEST_CASE(stop_closes_acceptor)
{
    boost::asio::io_context io;

    const unsigned short port = 19082;
    TCPServer server(io, port);
    server.start();

    server.stop();

    boost::asio::ip::tcp::socket client(io);
    boost::system::error_code ec;
    client.connect(
        boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"), port),
        ec);

    BOOST_CHECK(ec);
}

BOOST_AUTO_TEST_CASE(start_binds_to_requested_port)
{
    boost::asio::io_context io;

    const unsigned short port = 19083;
    TCPServer server(io, port);
    server.start();

    boost::asio::ip::tcp::socket client(io);
    boost::system::error_code ec;
    client.connect(
        boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"), port),
        ec);

    BOOST_CHECK(!ec);

    client.close(ec);
    server.stop();
}

BOOST_AUTO_TEST_SUITE_END()
