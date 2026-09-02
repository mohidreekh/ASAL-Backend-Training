#include "MessageFramer.hpp"

#include <algorithm>
#include <stdexcept>

std::vector<std::uint8_t> MessageFramer::frame(const std::string& message)
{
    if (message.size() > MAX_MESSAGE_SIZE) 
    {
        throw std::length_error("Message is too large");
    }

    const std::uint32_t length = static_cast<std::uint32_t>(message.size());

    std::vector<std::uint8_t> result(HEADER_SIZE + length);

    // Store length in big-endian format.
    result[0] = static_cast<std::uint8_t>((length >> 24) & 0xFF);
    result[1] = static_cast<std::uint8_t>((length >> 16) & 0xFF);
    result[2] = static_cast<std::uint8_t>((length >> 8) & 0xFF);
    result[3] = static_cast<std::uint8_t>(length & 0xFF);

    std::copy(message.begin(), message.end(), result.begin() + HEADER_SIZE);

    return result;
}


bool MessageFramer::extract(std::vector<std::uint8_t>& buffer, std::vector<std::string>& messages)
{
    bool extracted = false;

    while (true)
    {
        // Not enough data for the header.
        if (buffer.size() < HEADER_SIZE)
        {
            break;
        }

        const std::uint32_t length =
            (static_cast<std::uint32_t>(buffer[0]) << 24) |
            (static_cast<std::uint32_t>(buffer[1]) << 16) |
            (static_cast<std::uint32_t>(buffer[2]) << 8) |
            static_cast<std::uint32_t>(buffer[3]);

        if (length > MAX_MESSAGE_SIZE)
        {
            throw std::length_error("Message is too large");
        }

        const std::size_t totalSize = HEADER_SIZE + length;

        // Complete message has not arrived yet.
        if (buffer.size() < totalSize) 
        {
            break;
        }

        messages.emplace_back(buffer.begin() + HEADER_SIZE, buffer.begin() + totalSize);

        // Remove the processed message.
        buffer.erase(buffer.begin(), buffer.begin() + totalSize);

        extracted = true;
    }

    return extracted;
}