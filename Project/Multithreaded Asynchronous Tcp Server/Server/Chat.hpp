#pragma once

#include "ClientManager.hpp"
#include <memory>
#include <string>

class ClientSession;
class ClientManager;

class Chat
{
private:
    ClientManager _clientManager;

public:
    Chat() = default;

    void handleMessage(std::shared_ptr<ClientSession> client, const std::string& message);

    void removeClient(std::shared_ptr<ClientSession> client);

    void addClient(std::shared_ptr<ClientSession> client);

private:
    void _handleUsername(std::shared_ptr<ClientSession> client, const std::string& username);

    void _handleCommand(std::shared_ptr<ClientSession> client, const std::string& command);

    void _sendChatMessage(std::shared_ptr<ClientSession> client,const std::string& message);

    void _quit(std::shared_ptr<ClientSession> client);

    void _sendPrivateMessage(std::shared_ptr<ClientSession> client, const std::string& command);

    void _usersList(std::shared_ptr<ClientSession> client);

};