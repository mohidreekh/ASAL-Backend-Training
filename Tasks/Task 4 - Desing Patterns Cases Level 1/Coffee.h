#pragma once
#include <iostream>
#include<memory>
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
    virtual double price() const = 0;
    virtual ~Drink() = default;
};

class Coffee : public Drink
{
public:
    double price() const override
    {
        return 2.0;
    }
};

class CoffeeDecorator : public Drink{
protected:
    unique_ptr<Drink> wrapper;
public:
    CoffeeDecorator(unique_ptr<Drink> drink)
        : wrapper(move(drink)) {}

    double price() const override {
        return 0;
    }
};

class MilkCoffeeDecorator : public CoffeeDecorator {
public:
    MilkCoffeeDecorator(unique_ptr<Drink> drink)
        : CoffeeDecorator(move(drink)) {}

    double price() const override {
        return wrapper->price() + 0.5;
    }
};

class ChocolateDecorator : public CoffeeDecorator
{
public:
    ChocolateDecorator(unique_ptr<Drink> drink)
        : CoffeeDecorator(move(drink))
    {
    }

    double price() const override
    {
        return wrapper->price() + 1.0;
    }
};


class SugarDecorator : public CoffeeDecorator
{
public:
    SugarDecorator(unique_ptr<Drink> drink)
        : CoffeeDecorator(move(drink))
    {
    }

    double price() const override
    {
        return wrapper->price() + 0.2;
    }
};


class CoffeeDemo {
public:
    void demo() {
        //Drink* coffee = new Coffee();
        unique_ptr<Drink> coffee = make_unique<Coffee>();

        coffee = make_unique<MilkCoffeeDecorator>(move(coffee));
        coffee = make_unique<ChocolateDecorator>(move(coffee));
        coffee = make_unique<SugarDecorator>(move(coffee));

        cout << coffee->price();
    }
};