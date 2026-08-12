#pragma once
#include <string>
using namespace std;

//class Computer
//{
//public:
//    string cpu;
//    int ram;
//    string gpu;
//    string storage;
//    Computer(
//        string c,
//        int r,
//        string g,
//        string s)
//    {
//        cpu = c;
//        ram = r;
//        gpu = g;
//        storage = s;
//    }
//};
//
//int main()
//{
//    Computer pc(
//        "Intel i9",
//        64,
//        "RTX4090",
//        "2TB SSD"
//    );
//}


class Computer
{
private:
    string cpu;
    int ram;
    string gpu;
    string storage;
public:
    
    Computer() {
        cpu = "";
        ram = 0;
        gpu = "";
        storage = "";
    }
};

class Builder
{
public:
    virtual void buildCpu(string cpu) = 0;
    virtual void buildRam(int ram) = 0;
    virtual void buildGpu(string gpu) = 0;
    virtual void buildStorage(string storage) = 0;

    virtual Computer build() = 0;

    virtual ~Builder() = default;
};

class GamingComputerBuilder : public Builder
{
private:
    Computer computer;

public:
    void buildCpu(string cpu) override
    {
        computer.cpu = cpu;
    }

    void buildRam( int ram) override
    {
        computer.ram = ram;
    }

    void buildGpu(string gpu) override
    {
        computer.gpu = gpu;
    }

    void buildStorage(string storage) override
    {
        computer.storage = storage;
    }

    Computer build() override
    {
        return computer;
    }
};

class Director
{
public:
    Computer makeGamingComputer(Builder& builder)
    {
        builder.buildCpu("Intel Core i9");
        builder.buildRam(64);
        builder.buildGpu("C100");
        builder.buildStorage("2TB");

        return builder.build();
    }
};