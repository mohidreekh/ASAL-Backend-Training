#pragma once

#include <memory>
#include <vector>
#include <string>

class ClientSession;  // Forward declaration

class ClientManager
{
private:
    std::vector<std::shared_ptr<ClientSession>> _clients;

public:
    void add(std::shared_ptr<ClientSession> client);
    void remove(std::shared_ptr<ClientSession> client);
    void broadcast(const std::string& message, std::shared_ptr<ClientSession> sender);

    std::size_t size() const;
};