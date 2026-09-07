#pragma once

#include <cstdint>
#include <string>
#include <vector>

class MessageFramer
{
public:
    static std::vector<std::uint8_t>
        frame(const std::string& message);

    static bool
        extract(
            std::vector<std::uint8_t>& buffer,
            std::vector<std::string>& messages);

private:
    static constexpr std::size_t HEADER_SIZE = 4;
    static constexpr std::size_t MAX_MESSAGE_SIZE = 1024 * 1024;
};