#pragma once
#include <iostream>
using namespace std;

//class Coffee
//{
//public:
//
//    double price(
//        string milk,
//        bool sugar,
//        bool chocolate)
//    {
//        double cost = 2;
//
//        if (milk == "yes")
//            cost += 0.5;
//
//        if (sugar)
//            cost += 0.2;
//
//        if (chocolate)
//            cost += 1;
//
//        return cost;
//    }
//};

//Problem : Every new topping requires changing Coffee.
//
//Solutio : Using Decorator Pattern

class Drink {
public:
    virtual double price() = 0;
};

class Coffee : public Drink
{
public:
    double price() override
    {
        return 2.0;
    }
};

class CoffeeDecorator : public Drink{
protected:
    Drink* wrapper;
public:
    CoffeeDecorator(Drink* drink) {
        this->wrapper = drink;
    }
    double price() override {
        return 0;
    }
};

class MilkCoffeeDecorator : public CoffeeDecorator {
public:
    MilkCoffeeDecorator(Drink* drink) : CoffeeDecorator(drink) {}

    double price() override {
        return wrapper->price() + 0.5;
    }
};

class ChocolateDecorator : public CoffeeDecorator
{
public:
    ChocolateDecorator(Drink* drink)
        : CoffeeDecorator(drink)
    {
    }

    double price() override
    {
        return wrapper->price() + 1.0;
    }
};


class SugarDecorator : public CoffeeDecorator
{
public:
    SugarDecorator(Drink* drink)
        : CoffeeDecorator(drink)
    {
    }

    double price() override
    {
        return wrapper->price() + 0.2;
    }
};


class CoffeeDemo {
public:
    void demo() {
        Drink* coffee = new Coffee();

        coffee = new MilkCoffeeDecorator(coffee);
        coffee = new ChocolateDecorator(coffee);
        coffee = new SugarDecorator(coffee);

        cout << coffee->price();
    }
};