#include "ClientManager.hpp"
#include "ClientSession.hpp"

#include <algorithm>

void ClientManager::add(std::shared_ptr<ClientSession> client)
{
    std::lock_guard<std::mutex> lock(_mutex);
    _clients.push_back(std::move(client));
}

void ClientManager::remove(std::shared_ptr<ClientSession> client)
{
    std::lock_guard<std::mutex> lock(_mutex);

    _clients.erase(std::remove(_clients.begin(), _clients.end(), client), _clients.end());
}

void ClientManager::broadcast(const std::string& message, std::shared_ptr<ClientSession> sender)
{

    std::vector<std::shared_ptr<ClientSession>> vTempClients;

    {
        // Take a snapshot under the lock, then release it before sending
        // to avoid blocking other operations on _clients.
        std::lock_guard<std::mutex> lock(_mutex);
        vTempClients = _clients;
    }

    for (auto& client : vTempClients)
    {
        if (client != sender)
        {
            client->send(message);
        }
    }
}

std::size_t ClientManager::size() const
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _clients.size();
}

bool ClientManager::isUserExists(const std::string& username) const
{
    std::lock_guard<std::mutex> lock(_mutex);

    for (auto user : _clients)
    {
        if (user.get()->getUsername() == username)
        {
            return true;
        }
    }
    return false;
}


std::shared_ptr<ClientSession> ClientManager::findByUsername(const std::string& username) const
{
    std::lock_guard<std::mutex> lock(_mutex);

    for (const auto& client : _clients)
    {
        if (client->hasUserName() && client->getUsername() == username)
            return client;
    }

    return nullptr;
}

std::string ClientManager::getUsers() const
{
    std::lock_guard<std::mutex> lock(_mutex);

    std::string users = "Connected users:\n";

    for (const auto& client : _clients)
    {
        if (client->hasUserName())
            users += "- " + client->getUsername() + "\n";
    }

    return users;
}