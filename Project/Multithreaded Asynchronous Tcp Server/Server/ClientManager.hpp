#pragma once

#include <memory>
#include <vector>
#include <string>
#include <mutex>

class ClientSession;  // Forward declaration

class ClientManager
{
private:
    std::vector<std::shared_ptr<ClientSession>> _clients;
    mutable std::mutex _mutex;

public:
    void add(std::shared_ptr<ClientSession> client);
    void remove(std::shared_ptr<ClientSession> client);
    void broadcast(const std::string& message, std::shared_ptr<ClientSession> sender);
    std::shared_ptr<ClientSession> findByUsername(const std::string& username) const;
    bool isUserExists(const std::string& username) const;
    std::size_t size() const;
    std::string getUsers() const;
};