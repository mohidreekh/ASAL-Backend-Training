#include "ClientManager.hpp"
#include "ClientSession.hpp"

#include <algorithm>

void ClientManager::add(std::shared_ptr<ClientSession> client)
{
    _clients.push_back(std::move(client));
}

void ClientManager::remove(std::shared_ptr<ClientSession> client)
{
    _clients.erase(std::remove(_clients.begin(), _clients.end(), client), _clients.end());
}

void ClientManager::broadcast(const std::string& message, std::shared_ptr<ClientSession> sender)
{
    for (auto& client : _clients)
    {
        if (client != sender)
        {
            client->send(message);
        }
    }
}

std::size_t ClientManager::size() const
{
    return _clients.size();
}