#pragma once
#include <iostream>
#include <memory>
#include <map>

using namespace std;

//class OrderProcessor
//{
//public:
//    void process(string type)
//    {
//        if (type == "card")
//        {
//            cout << "Processing Credit Card Payment\n";
//        }
//        else if (type == "paypal")
//        {
//            cout << "Processing PayPal Payment\n";
//        }
//        else if (type == "crypto")
//        {
//            cout << "Processing Crypto Payment\n";
//        }
//    }
//};

//PROBLEM : If we want to add new payment method we should modify the class.

// ==================================
// Solution 1 : Strategy Pattern
// ==================================

class Pay
{
public:
    virtual void process() const = 0;
    virtual ~Pay() = default;
};

class Card : public Pay
{
public:
    void process() const override
    {
        cout << "Processing Card Payment\n";
    }
};

class PayPal : public Pay
{
public:
    void process() const override
    {
        cout << "Processing PayPal Payment\n";
    }
};

class Crypto : public Pay
{
public:
    void process() const override
    {
        cout << "Processing Crypto Payment\n";
    }
};

class OrderProcessor
{
public:
    void process(const Pay& pay) const
    {
        pay.process();
    }
};

class PaymentDemo
{
public:
    void demo()
    {
        OrderProcessor processor;

        auto paypal = make_unique<PayPal>();
        auto card = make_unique<Card>();
        auto crypto = make_unique<Crypto>();

        processor.process(*paypal);
        processor.process(*card);
        processor.process(*crypto);
    }
};

// ==================================
// Solution 2 : Factory Pattern
// ==================================
class PaymentFactory
{
private:
    using Creator = unique_ptr<Pay>(*)();

    static map<string, Creator>& getCreators()
{
    static map<string, Creator> creators
    {
        {
            "card",
            []() -> unique_ptr<Pay>
            {
                return make_unique<Card>();
            }
        },

        {
            "paypal",
            []() -> unique_ptr<Pay>
            {
                return make_unique<PayPal>();
            }
        },

        {
            "crypto",
            []() -> unique_ptr<Pay>
            {
                return make_unique<Crypto>();
            }
        }
    };

    return creators;
}

public:
    static unique_ptr<Pay> create(const string& type)
    {
        auto& creators = getCreators();

        auto it = creators.find(type);

        if (it != creators.end())
        {
            return it->second();
        }

        return nullptr;
    }
};

class PaymentFactoryDemo
{
public:
    void demo()
    {
        auto payment = PaymentFactory::create("paypal");

        if (payment)
        {
            payment->process();
        }
    }
};