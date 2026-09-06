#pragma once

#include <boost/asio.hpp>
#include <vector>
#include<deque>
#include<memory>
#include <functional>

using namespace boost::asio;

class ClientSession : public std::enable_shared_from_this<ClientSession>
{
private:
	ip::tcp::socket _socket;

	// Ensures handlers for this session are not executed concurrently.
	strand<any_io_executor> _strand;

	// Temporary buffer used by Asio.
	std::vector<char> _vBuffer;

	// Stores bytes that have not been converted into complete messages yet.
	std::vector<std::uint8_t> incomingBuffer;

	std::deque<std::vector<uint8_t>> _writeQueue;

	std::function<void()> _onDisconnect;

	std::function<void(const std::string&)> _onMessage;

	std::string _username = "Anonymous";

	bool _disconnected = false;

	
public:
	ClientSession(ip::tcp::socket socket);

	void start();

	void setOnDisconnect(std::function<void()> callback);

	void send(const std::string& message);

	void setOnMessage(std::function<void(const std::string&)> callback);

	void setUsername(const std::string& username);

	const std::string& getUsername() const;

	void disconnect();

	const bool hasUserName();

private:
	void _read();
	void _handleMessage(const std::string& message);
	void _write();
	void _send(std::vector<uint8_t> data);
};

