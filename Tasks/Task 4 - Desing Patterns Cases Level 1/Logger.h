#pragma once
#include <iostream>
using namespace std;

//class Logger
//{
//public:
//
//    void log(string message)
//    {
//        cout << message << endl;
//    }
//};
//
//
//void server()
//{
//    Logger logger;
//    logger.log("Server started");
//}
//
//
//void database()
//{
//    Logger logger;
//    logger.log("Database connected");
//}
//


//Problem : Multiple logger instances exist.
//
//Solution : Using Sigleton Pattern to prevent make multiple objects

class Logger
{
    Logger() {}
    static Logger* instance;

public:
    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }

    void log(string message)
    {
        cout << message << endl;
    }
};

void server()
{
    Logger &logger = Logger::getInstance();
    logger.log("Server started");
}

void database()
{
    Logger &logger = Logger::getInstance();
    logger.log("Database connected");
}