#include <boost/test/unit_test.hpp>

#include "ClientSession.hpp"
#include "MessageFramer.hpp"
#include "TestHelpers.hpp"

#include <boost/asio.hpp>
#include <functional>
#include <string>
#include <vector>

BOOST_AUTO_TEST_SUITE(ClientSessionTests)

BOOST_AUTO_TEST_CASE(start_prompts_for_username)
{
    boost::asio::io_context io;

    auto [session, client] = test_helpers::makeConnectedSessionPair(io);
    session->start();

    const auto messages = test_helpers::drainSentMessages(io, client);

    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_CHECK_EQUAL(messages[0], "Enter Username :");
}

BOOST_AUTO_TEST_CASE(send_delivers_framed_message)
{
    boost::asio::io_context io;

    auto [session, client] = test_helpers::makeConnectedSessionPair(io);
    session->send("hello");

    const auto messages = test_helpers::drainSentMessages(io, client);

    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_CHECK_EQUAL(messages[0], "hello");
}

BOOST_AUTO_TEST_CASE(on_message_callback_receives_parsed_input)
{
    boost::asio::io_context io;

    auto [session, client] = test_helpers::makeConnectedSessionPair(io);

    std::string received;
    session->setOnMessage([&received](const std::string& message)
        {
            received = message;
        });

    session->start();
    test_helpers::drainSentMessages(io, client);

    const auto payload = MessageFramer::frame("test message");
    boost::asio::write(client, boost::asio::buffer(payload));

    test_helpers::runIoUntil(io, 64);

    BOOST_CHECK_EQUAL(received, "test message");
}

BOOST_AUTO_TEST_CASE(on_disconnect_callback_is_invoked)
{
    boost::asio::io_context io;

    auto [session, client] = test_helpers::makeConnectedSessionPair(io);

    bool disconnected = false;
    session->setOnDisconnect([&disconnected]()
        {
            disconnected = true;
        });

    session->disconnect();

    BOOST_CHECK(disconnected);
}

BOOST_AUTO_TEST_CASE(has_username_is_false_until_set)
{
    boost::asio::io_context io;

    auto [session, client] = test_helpers::makeConnectedSessionPair(io);
    (void)client;

    BOOST_CHECK(!session->hasUserName());

    session->setUsername("alice");

    BOOST_CHECK(session->hasUserName());
    BOOST_CHECK_EQUAL(session->getUsername(), "alice");
}

BOOST_AUTO_TEST_CASE(disconnect_is_idempotent)
{
    boost::asio::io_context io;

    auto [session, client] = test_helpers::makeConnectedSessionPair(io);
    (void)client;

    int callbackCount = 0;
    session->setOnDisconnect([&callbackCount]()
        {
            ++callbackCount;
        });

    session->disconnect();
    session->disconnect();

    BOOST_CHECK_EQUAL(callbackCount, 1);
}

BOOST_AUTO_TEST_SUITE_END()
