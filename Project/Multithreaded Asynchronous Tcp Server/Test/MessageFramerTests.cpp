#include <boost/test/unit_test.hpp>

#include "MessageFramer.hpp"

#include <cstdint>
#include <string>
#include <vector>

BOOST_AUTO_TEST_CASE(frame_empty_message)
{
    auto packet = MessageFramer::frame("");

    BOOST_CHECK_EQUAL(packet.size(), 4);

    BOOST_CHECK_EQUAL(packet[0], 0);
    BOOST_CHECK_EQUAL(packet[1], 0);
    BOOST_CHECK_EQUAL(packet[2], 0);
    BOOST_CHECK_EQUAL(packet[3], 0);
}

BOOST_AUTO_TEST_CASE(frame_message)
{
    const std::string message = "Hello";

    auto packet = MessageFramer::frame(message);

    BOOST_CHECK_EQUAL(packet.size(), 9);
}

BOOST_AUTO_TEST_CASE(frame_stores_length_in_big_endian)
{
    const std::string message = "Hello";

    auto packet = MessageFramer::frame(message);

    BOOST_CHECK_EQUAL(packet[0], 0);
    BOOST_CHECK_EQUAL(packet[1], 0);
    BOOST_CHECK_EQUAL(packet[2], 0);
    BOOST_CHECK_EQUAL(packet[3], 5);
}   


BOOST_AUTO_TEST_CASE(extract_complete_message)
{
    auto packet = MessageFramer::frame("Hello");

    std::vector<std::uint8_t> buffer = packet;
    std::vector<std::string> messages;

    bool result =
        MessageFramer::extract(buffer, messages);

    BOOST_CHECK(result);
    BOOST_CHECK_EQUAL(messages.size(), 1);
    BOOST_CHECK_EQUAL(messages[0], "Hello");
    BOOST_CHECK(buffer.empty());
}


BOOST_AUTO_TEST_CASE(extract_waits_for_partial_header)
{
    auto packet = MessageFramer::frame("Hello");

    std::vector<std::uint8_t> buffer(
        packet.begin(),
        packet.begin() + 2);

    std::vector<std::string> messages;

    bool result =
        MessageFramer::extract(buffer, messages);

    BOOST_CHECK(!result);
    BOOST_CHECK(messages.empty());
}



BOOST_AUTO_TEST_CASE(extract_waits_for_partial_body)
{
    auto packet = MessageFramer::frame("Hello");

    std::vector<std::uint8_t> buffer(
        packet.begin(),
        packet.begin() + 6);

    std::vector<std::string> messages;

    bool result =
        MessageFramer::extract(buffer, messages);

    BOOST_CHECK(!result);
    BOOST_CHECK(messages.empty());

    BOOST_CHECK_EQUAL(buffer.size(), 6);
}

BOOST_AUTO_TEST_CASE(extract_multiple_messages)
{
    auto packet1 = MessageFramer::frame("Hello");
    auto packet2 = MessageFramer::frame("World");

    std::vector<std::uint8_t> buffer;

    buffer.insert(
        buffer.end(),
        packet1.begin(),
        packet1.end());

    buffer.insert(
        buffer.end(),
        packet2.begin(),
        packet2.end());

    std::vector<std::string> messages;

    bool result =
        MessageFramer::extract(buffer, messages);

    BOOST_CHECK(result);

    BOOST_CHECK_EQUAL(messages.size(), 2);

    BOOST_CHECK_EQUAL(messages[0], "Hello");
    BOOST_CHECK_EQUAL(messages[1], "World");

    BOOST_CHECK(buffer.empty());
}

BOOST_AUTO_TEST_CASE(extract_empty_buffer)
{
    std::vector<std::uint8_t> buffer;
    std::vector<std::string> messages;

    bool result =
        MessageFramer::extract(buffer, messages);

    BOOST_CHECK(!result);
    BOOST_CHECK(messages.empty());
}

BOOST_AUTO_TEST_CASE(frame_rejects_oversized_message)
{
    std::string message(
        1024 * 1024 + 1,
        'A');

    BOOST_CHECK_THROW(
        MessageFramer::frame(message),
        std::length_error);
}

BOOST_AUTO_TEST_CASE(frame_preserves_message_content)
{
    const std::string message = "Hello, world!";

    auto packet = MessageFramer::frame(message);

    BOOST_CHECK_EQUAL(
        std::string(packet.begin() + 4, packet.end()),
        message);
}

BOOST_AUTO_TEST_CASE(extract_rejects_oversized_length)
{
    std::vector<std::uint8_t> buffer = { 0, 0x10, 0, 1, 'x' };
    std::vector<std::string> messages;

    BOOST_CHECK_THROW(
        MessageFramer::extract(buffer, messages),
        std::length_error);
}

BOOST_AUTO_TEST_CASE(extract_one_message_leaves_remainder_in_buffer)
{
    auto packet1 = MessageFramer::frame("first");
    auto packet2 = MessageFramer::frame("second");

    std::vector<std::uint8_t> buffer(
        packet1.begin(),
        packet1.end());

    buffer.insert(buffer.end(), packet2.begin(), packet2.begin() + 3);

    std::vector<std::string> messages;
    bool result = MessageFramer::extract(buffer, messages);

    BOOST_CHECK(result);
    BOOST_CHECK_EQUAL(messages.size(), 1);
    BOOST_CHECK_EQUAL(messages[0], "first");
    BOOST_CHECK(!buffer.empty());
}