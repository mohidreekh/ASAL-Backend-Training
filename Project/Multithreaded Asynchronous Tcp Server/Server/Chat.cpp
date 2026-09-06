#include "Chat.hpp"

#include "ClientManager.hpp"
#include "ClientSession.hpp"

#include <iostream>
#include <sstream>

void Chat::handleMessage(std::shared_ptr<ClientSession> client, const std::string& message)
{
    if (!client->hasUserName())
    {
        _handleUsername(client, message);
        return;
    }

    if (!message.empty() && message[0] == '/')
    {
        _handleCommand(client, message);
        return;
    }

    _sendChatMessage(client, message);
}

void Chat::removeClient(std::shared_ptr<ClientSession> client)
{
    _clientManager.remove(client);
}

void Chat::_handleUsername(std::shared_ptr<ClientSession> client, const std::string& username)
{
    if (username.size() < 3)
    {
        client->send("Username should be 3 or more chars. Try again:");
        return;
    }

    if (_clientManager.isUserExists(username))
    {
        client->send("Username already taken. Try another one:");
        return;
    }

    client->setUsername(username);
    client->send("Welcome " + client->getUsername());

    std::cout << "Client identified as: " << client->getUsername() << '\n';
}

void Chat::_handleCommand(std::shared_ptr<ClientSession> client, const std::string& command)
{
    if (command == "/users")
    {
        _usersList(client);
        return;
    }

    if (command == "/quit")
    {
        _quit(client);
        return;
    }

    if (command.rfind("/msg ", 0) == 0)
    {
        _sendPrivateMessage(client, command);
        return;
    }

    client->send("Unknown command.");
}

//void Chat::_users(std::shared_ptr<ClientSession> client)
//{
//    client->send(_clientManager.getUsers());
//}

void Chat::_quit(std::shared_ptr<ClientSession> client)
{
    client->send("Goodbye!");
    client->disconnect();
}

void Chat::_sendPrivateMessage(std::shared_ptr<ClientSession> client, const std::string& command)
{
    std::istringstream stream(command);
    std::string commandName;
    std::string username;

    stream >> commandName >> username;

    std::string message;
    std::getline(stream, message);

    if (!message.empty() && message[0] == ' ')
        message.erase(0, 1);

    if (username.empty() || message.empty())
    {
        client->send("Usage: /msg <username> <message>");
        return;
    }

    auto target = _clientManager.findByUsername(username);

    if (!target)
    {
        client->send("User not found.");
        return;
    }

    target->send("[Private] " + client->getUsername() + ": " + message);
}

void Chat::_sendChatMessage(std::shared_ptr<ClientSession> client, const std::string& message)
{
    std::string fullMessage = client->getUsername() + ": " + message;
    _clientManager.broadcast(fullMessage, client);
}

void Chat::_usersList(std::shared_ptr<ClientSession> client)
{
    client->send(_clientManager.getUsers());
}

void Chat::addClient(std::shared_ptr<ClientSession> client)
{
    _clientManager.add(client);

    std::cout << "Client connected. Total Clients : " << _clientManager.size() << '\n';

    client->setOnMessage(
        [this, client](const std::string& message)
        {
            handleMessage(client, message);
        });

    client->setOnDisconnect(    
        [this, client]()
        {
            removeClient(client);
        });
}