#include <boost/test/unit_test.hpp>

#include "Chat.hpp"
#include "TestHelpers.hpp"

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace
{
    struct RegisteredClient
    {
        std::shared_ptr<ClientSession> session;
        boost::asio::ip::tcp::socket client;
    };

    RegisteredClient registerUser(Chat& chat, boost::asio::io_context& io, const std::string& username)
    {
        auto [session, client] = test_helpers::makeConnectedSessionPair(io);
        chat.addClient(session);

        test_helpers::drainSentMessages(io, client);
        chat.handleMessage(session, username);
        test_helpers::drainSentMessages(io, client);

        return { session, std::move(client) };
    }
}

BOOST_AUTO_TEST_SUITE(ChatTests)


BOOST_AUTO_TEST_CASE(username_must_be_at_least_three_characters)
{
    boost::asio::io_context io;
    Chat chat;

    auto [session, client] = test_helpers::makeConnectedSessionPair(io);
    chat.addClient(session);
    test_helpers::drainSentMessages(io, client);

    chat.handleMessage(session, "ab");

    const auto messages = test_helpers::drainSentMessages(io, client);

    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_CHECK_EQUAL(messages[0], "Username should be 3 or more chars. Try again:");
    BOOST_CHECK(!session->hasUserName());
}

BOOST_AUTO_TEST_CASE(username_must_be_unique)
{
    boost::asio::io_context io;
    Chat chat;

    registerUser(chat, io, "alice");

    auto [session, client] = test_helpers::makeConnectedSessionPair(io);
    chat.addClient(session);
    test_helpers::drainSentMessages(io, client);

    chat.handleMessage(session, "alice");

    const auto messages = test_helpers::drainSentMessages(io, client);

    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_CHECK_EQUAL(messages[0], "Username already taken. Try another one:");
    BOOST_CHECK(!session->hasUserName());
}

BOOST_AUTO_TEST_CASE(valid_username_is_accepted)
{
    boost::asio::io_context io;
    Chat chat;

    auto [session, client] = test_helpers::makeConnectedSessionPair(io);
    chat.addClient(session);
    test_helpers::drainSentMessages(io, client);

    chat.handleMessage(session, "alice");

    const auto messages = test_helpers::drainSentMessages(io, client);

    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_CHECK_EQUAL(messages[0], "Welcome alice");
    BOOST_CHECK(session->hasUserName());
}

BOOST_AUTO_TEST_CASE(chat_message_is_broadcast_to_other_users)
{
    boost::asio::io_context io;
    Chat chat;

    registerUser(chat, io, "alice");

    auto bob = registerUser(chat, io, "bob");
    auto carol = registerUser(chat, io, "carol");

    chat.handleMessage(bob.session, "hello room");

    const auto carolMessages = test_helpers::drainSentMessages(io, carol.client);
    const auto bobMessages = test_helpers::drainSentMessages(io, bob.client);

    BOOST_CHECK(bobMessages.empty());
    BOOST_REQUIRE_EQUAL(carolMessages.size(), 1);
    BOOST_CHECK_EQUAL(carolMessages[0], "bob: hello room");
}

BOOST_AUTO_TEST_CASE(users_command_returns_connected_users)
{
    boost::asio::io_context io;
    Chat chat;

    registerUser(chat, io, "alice");
    auto bob = registerUser(chat, io, "bob");

    chat.handleMessage(bob.session, "/users");

    const auto messages = test_helpers::drainSentMessages(io, bob.client);

    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_CHECK(messages[0].find("alice") != std::string::npos);
    BOOST_CHECK(messages[0].find("bob") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(private_message_reaches_target_user)
{
    boost::asio::io_context io;
    Chat chat;

    auto alice = registerUser(chat, io, "alice");
    auto bob = registerUser(chat, io, "bob");

    chat.handleMessage(bob.session, "/msg alice secret note");

    const auto aliceMessages = test_helpers::drainSentMessages(io, alice.client);
    const auto bobMessages = test_helpers::drainSentMessages(io, bob.client);

    BOOST_CHECK(bobMessages.empty());
    BOOST_REQUIRE_EQUAL(aliceMessages.size(), 1);
    BOOST_CHECK_EQUAL(aliceMessages[0], "[Private] bob: secret note");
}

BOOST_AUTO_TEST_CASE(private_message_requires_usage_when_incomplete)
{
    boost::asio::io_context io;
    Chat chat;

    auto bob = registerUser(chat, io, "bob");

    chat.handleMessage(bob.session, "/msg alice");

    const auto messages = test_helpers::drainSentMessages(io, bob.client);

    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_CHECK_EQUAL(messages[0], "Usage: /msg <username> <message>");
}

BOOST_AUTO_TEST_CASE(private_message_reports_missing_user)
{
    boost::asio::io_context io;
    Chat chat;

    auto alice = registerUser(chat, io, "alice");

    chat.handleMessage(alice.session, "/msg ghost hi");

    const auto messages = test_helpers::drainSentMessages(io, alice.client);

    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_CHECK_EQUAL(messages[0], "User not found.");
}

BOOST_AUTO_TEST_CASE(unknown_command_returns_error)
{
    boost::asio::io_context io;
    Chat chat;

    auto alice = registerUser(chat, io, "alice");

    chat.handleMessage(alice.session, "/unknown");

    const auto messages = test_helpers::drainSentMessages(io, alice.client);

    BOOST_REQUIRE_EQUAL(messages.size(), 1);
    BOOST_CHECK_EQUAL(messages[0], "Unknown command.");
}

BOOST_AUTO_TEST_SUITE_END()
