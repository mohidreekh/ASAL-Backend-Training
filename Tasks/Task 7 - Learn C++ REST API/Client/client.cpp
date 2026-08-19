#include "httplib.h"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

void printResponse(const httplib::Result& result)
{
    if (!result) {
        std::cout << "Request failed: Unable to connect to server\n";
        return;
    }

    std::cout << "Status: " << result->status << "\n";
    std::cout << "Response:\n" << result->body << "\n";
}

int main()
{
    httplib::Client client("http://localhost:8000");

    std::cout << "================================\n";
    std::cout << "       C++ HTTP CLIENT\n";
    std::cout << "================================\n\n";

    // GET USER
    std::cout << "=== GET USER ===\n";

    auto result = client.Get("/user/1");

    if (!result) {
        std::cout << "Request failed: Unable to connect to server\n";
        return 1;
    }

    if (result->status >= 400) {
        std::cout << "HTTP Error: " << result->status << "\n";
    }

    printResponse(result);

    // CREATE USER
    std::cout << "\n=== CREATE USER ===\n";

    json user;
    user["id"] = "1";
    user["username"] = "Ahmad";
    user["age"] = 20;

    result = client.Post("/user", user.dump(), "application/json");

    if (!result) {
        std::cout << "Request failed: Unable to connect to server\n";
        return 1;
    }

    if (result->status >= 400) {
        std::cout << "HTTP Error: " << result->status << "\n";
    }

    printResponse(result);

    // UPDATE USER
    std::cout << "\n=== UPDATE USER ===\n";

    json update;
    update["username"] = "Mohammad";
    update["age"] = 25;

    result = client.Put("/user/1", update.dump(), "application/json");

    if (!result) {
        std::cout << "Request failed: Unable to connect to server\n";
        return 1;
    }

    if (result->status >= 400) {
        std::cout << "HTTP Error: " << result->status << "\n";
    }

    printResponse(result);

    // DELETE USER
    std::cout << "\n=== DELETE USER ===\n";

    result = client.Delete("/user/1");

    if (!result) {
        std::cout << "Request failed: Unable to connect to server\n";
        return 1;
    }

    if (result->status >= 400) {
        std::cout << "HTTP Error: " << result->status << "\n";
    }

    printResponse(result);

    std::cout << "\n================================\n";
    std::cout << "       TASK COMPLETED\n";
    std::cout << "================================\n";
}