#include <boost/asio.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include "MessageFramer.hpp"

using boost::asio::ip::tcp;

class ChatClient
{
private:
    boost::asio::io_context& io;
    tcp::socket socket;

    std::vector<char> readBuffer;
    std::vector<std::uint8_t> incomingBuffer;

public:

    ChatClient(boost::asio::io_context& io)
        : io(io), socket(io), readBuffer(1024)
    {}

    void connect(const std::string& host, unsigned short port)
    {
        tcp::endpoint endpoint(boost::asio::ip::make_address(host), port);
        socket.connect(endpoint);
        printHeader();
        startReading();
    }

    void send(const std::string& message)
    {
        auto packet = MessageFramer::frame(message);

        boost::asio::write(socket, boost::asio::buffer(packet));
    }

private:

    void printHeader()
    {
        std::cout << "\n";
        std::cout << "=============================================\n";
        std::cout << "              TCP CHAT CLIENT\n";
        std::cout << "=============================================\n";
        std::cout << " Connected to: 127.0.0.1:8080\n";
        std::cout << " Available commands:\n";
        std::cout << "   /users                    - List connected users\n";
        std::cout << "   /msg <username> <message> - Send a private message\n";
        std::cout << "   /quit                     - Disconnect from the server\n";
        std::cout << "---------------------------------------------\n";
    }

    void startReading()
    {
        socket.async_read_some(
            boost::asio::buffer(readBuffer),

            [this](
                const boost::system::error_code& error,
                std::size_t bytesRead)
            {
                if (error)
                {
                    if (error == boost::asio::error::eof)
                    {
                        std::cout
                            << "\n\n"
                            << "[System] Server disconnected.\n";
                    }
                    else
                    {
                        std::cerr
                            << "\n\n"
                            << "[Error] "
                            << error.message()
                            << '\n';
                    }

                    return;
                }

                incomingBuffer.insert(incomingBuffer.end(), reinterpret_cast<std::uint8_t*>(readBuffer.data()),
                    reinterpret_cast<std::uint8_t*>(readBuffer.data()) + bytesRead);

                processMessages();

                startReading();
            }
        );
    }

    void processMessages()
    {
        std::vector<std::string> messages;

        try
        {
            MessageFramer::extract(incomingBuffer, messages);

            for (const auto& message : messages)
            {
                std::cout << "\n";
                std::cout << "[CHAT] " << message << '\n';
                std::cout << "You: ";
                std::cout.flush();
            }
        }
        catch (const std::exception& ex)
        {
            std::cerr << "\n" << "[Framing Error] " << ex.what() << '\n';
        }
    }
};


int main()
{
    try
    {
        boost::asio::io_context io;

        ChatClient client(io);

        client.connect("127.0.0.1",8080);

        // Run asynchronous operations
        // in a separate thread.
        std::thread ioThread([&io]()
            {
                io.run();
            });

        std::string message;

        while (true)
        {
            std::cout << "You: ";
            std::cout.flush();

            std::getline(std::cin,message);

            if (message == "/quit")
            {
                client.send(message);
                break;
            }

            if (!message.empty())
            {
                client.send(message);
            }
        }

        io.stop();

        if (ioThread.joinable())
        {
            ioThread.join();
        }
    }
    catch (const std::exception& ex)
    {
        std::cerr << "\n" << "[Error] " << ex.what() << '\n';
    }

    return 0;
}