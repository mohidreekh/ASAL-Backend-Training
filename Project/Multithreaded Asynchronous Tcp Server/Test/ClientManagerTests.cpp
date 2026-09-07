#include <boost/test/unit_test.hpp>

#include "ClientManager.hpp"
#include "TestHelpers.hpp"

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <vector>

BOOST_AUTO_TEST_SUITE(ClientManagerTests)

BOOST_AUTO_TEST_CASE(add_increases_size)
{
    boost::asio::io_context io;
    ClientManager manager;

    auto session = test_helpers::makeNamedSession(io, "alice");

    BOOST_CHECK_EQUAL(manager.size(), 0);
    manager.add(session);
    BOOST_CHECK_EQUAL(manager.size(), 1);
}

BOOST_AUTO_TEST_CASE(remove_decreases_size)
{
    boost::asio::io_context io;
    ClientManager manager;

    auto session = test_helpers::makeNamedSession(io, "alice");
    manager.add(session);

    manager.remove(session);

    BOOST_CHECK_EQUAL(manager.size(), 0);
}

BOOST_AUTO_TEST_CASE(remove_nonexistent_client_is_safe)
{
    boost::asio::io_context io;
    ClientManager manager;

    auto session = test_helpers::makeNamedSession(io, "alice");

    manager.remove(session);

    BOOST_CHECK_EQUAL(manager.size(), 0);
}

BOOST_AUTO_TEST_CASE(is_user_exists_detects_registered_username)
{
    boost::asio::io_context io;
    ClientManager manager;

    auto alice = test_helpers::makeNamedSession(io, "alice");
    auto bob = test_helpers::makeNamedSession(io, "bob");

    manager.add(alice);
    manager.add(bob);

    BOOST_CHECK(manager.isUserExists("alice"));
    BOOST_CHECK(manager.isUserExists("bob"));
    BOOST_CHECK(!manager.isUserExists("charlie"));
}

BOOST_AUTO_TEST_CASE(find_by_username_returns_matching_session)
{
    boost::asio::io_context io;
    ClientManager manager;

    auto alice = test_helpers::makeNamedSession(io, "alice");
    manager.add(alice);

    auto found = manager.findByUsername("alice");

    BOOST_REQUIRE(found);
    BOOST_CHECK_EQUAL(found->getUsername(), "alice");
}

BOOST_AUTO_TEST_CASE(find_by_username_ignores_anonymous_sessions)
{
    boost::asio::io_context io;
    ClientManager manager;

    auto [session, client] = test_helpers::makeConnectedSessionPair(io);
    (void)client;

    manager.add(session);

    BOOST_CHECK(!manager.findByUsername("Anonymous"));
    BOOST_CHECK(!manager.findByUsername(""));
}

BOOST_AUTO_TEST_CASE(get_users_lists_named_clients_only)
{
    boost::asio::io_context io;
    ClientManager manager;

    auto alice = test_helpers::makeNamedSession(io, "alice");
    auto bob = test_helpers::makeNamedSession(io, "bob");
    auto [anonymous, client] = test_helpers::makeConnectedSessionPair(io);
    (void)client;

    manager.add(alice);
    manager.add(bob);
    manager.add(anonymous);

    const std::string users = manager.getUsers();

    BOOST_CHECK(users.find("alice") != std::string::npos);
    BOOST_CHECK(users.find("bob") != std::string::npos);
    BOOST_CHECK(users.find("Anonymous") == std::string::npos);
}

BOOST_AUTO_TEST_CASE(broadcast_sends_to_other_clients_not_sender)
{
    boost::asio::io_context io;
    ClientManager manager;

    auto [sender, senderClient] = test_helpers::makeConnectedSessionPair(io);
    auto [receiver, receiverClient] = test_helpers::makeConnectedSessionPair(io);

    sender->setUsername("sender");
    receiver->setUsername("receiver");

    manager.add(sender);
    manager.add(receiver);

    manager.broadcast("hello everyone", sender);

    const auto senderMessages = test_helpers::drainSentMessages(io, senderClient);
    const auto receiverMessages = test_helpers::drainSentMessages(io, receiverClient);

    BOOST_CHECK(senderMessages.empty());
    BOOST_REQUIRE_EQUAL(receiverMessages.size(), 1);
    BOOST_CHECK_EQUAL(receiverMessages[0], "hello everyone");
}

BOOST_AUTO_TEST_SUITE_END()
