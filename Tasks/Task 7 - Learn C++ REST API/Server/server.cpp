#include "httplib.h"
#include "json.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

using json = nlohmann::json;

struct User {
    std::string id;
    std::string username;
    int age;

    User(std::string id, std::string username, int age)
        : id(id), username(username), age(age) {
    }
};

int main()
{
    httplib::Server server;
    std::vector<User> users;

    users.push_back(User("1", "mohidreekh", 21));

    // GET /user/1
    server.Get(R"(/user/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
        std::string id = req.matches[1];

        auto it = std::find_if(users.begin(), users.end(), [id](const User& user) {
            return user.id == id;
            });

        if (it == users.end()) {
            res.status = 404;
            res.set_content(R"({"message":"User not found"})", "application/json");
            return;
        }

        json data;
        data["id"] = it->id;
        data["username"] = it->username;
        data["age"] = std::to_string(it->age);

        res.set_content(data.dump(), "application/json");
        });

    // POST /user
    server.Post("/user", [&](const httplib::Request& req, httplib::Response& res) {
        try {
            json data = json::parse(req.body);

            if (!data.contains("id") || !data.contains("username") || !data.contains("age")) {
                res.status = 400;
                res.set_content(R"({"message":"Bad Request"})", "application/json");
                return;
            }

            std::string id = data["id"];
            std::string username = data["username"];
            int age = data["age"];

            users.push_back(User(id, username, age));

            res.status = 201;
            res.set_content(R"({"message":"User created"})", "application/json");
        }
        catch (...) {
            res.status = 400;
            res.set_content(R"({"message":"Invalid JSON"})", "application/json");
        }
        });


    // PUT /user/1
    server.Put(R"(/user/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
        std::string id = req.matches[1];

        auto it = std::find_if(users.begin(), users.end(), [id](const User& user) {
            return user.id == id;
            });

        if (it == users.end()) {
            res.status = 404;
            res.set_content(R"({"message":"User not found"})", "application/json");
            return;
        }

        json data = json::parse(req.body);

        it->username = data["username"];
        it->age = data["age"];

        res.set_content(R"({"message":"User updated"})", "application/json");
        });

    // DELETE /user/1
    server.Delete(R"(/user/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
        std::string id = req.matches[1];

        auto it = std::find_if(users.begin(), users.end(), [id](const User& user) {
            return user.id == id;
            });

        if (it == users.end()) {
            res.status = 404;
            res.set_content(R"({"message":"User not found"})", "application/json");
            return;
        }

        users.erase(it);

        res.set_content(R"({"message":"User deleted"})", "application/json");
        });

    std::cout << "start listing at port 8000" << std::endl;
    server.listen("localhost", 8000);
}