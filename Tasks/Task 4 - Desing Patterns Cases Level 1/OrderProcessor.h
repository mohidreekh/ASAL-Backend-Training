#pragma once
#include <iostream>
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
//************************************
//SOLUTION  1: Using Strategy Pattern.
//************************************

class Pay {
public:
	virtual void process() = 0;
};


class Card : public Pay {
	void process() {
		cout << "Processing Card Payment" << endl;
	}
};

class PayPal : public Pay {
	void process() {
		cout << "Processing PayPal Payment" << endl;
	}
};

class Crypto : public Pay {
	void process() {
		cout << "Processing Crypto Payment" << endl;
	}
};

class OrderProcessor
{
public:
    void process(Pay* pay)
    {
		pay->process();
    }
};

class PayemntDemo {
public:
	void demo() {
		OrderProcessor processor;

		Pay* paypal = new PayPal();
		Pay* card = new Card();
		Pay* crypto = new Crypto();

		processor.process(paypal);
		processor.process(card);
		processor.process(crypto);
	}
};

//**********************************
//SOLUTION 2 : Using Factory Pattern
//**********************************
#include<map>

class Pay
{
public:
    virtual void process() = 0;
    virtual ~Pay() = default;
};


// Concrete Products

class Card : public Pay
{
public:
    void process() override
    {
        cout << "Processing Card Payment\n";
    }
};


class PayPal : public Pay
{
public:
    void process() override
    {
        cout << "Processing PayPal Payment\n";
    }
};


class Crypto : public Pay
{
public:
    void process() override
    {
        cout << "Processing Crypto Payment\n";
    }
};


class PaymentFactory
{
private:

    using Creator = Pay * (*)();

    static map<string, Creator>& getCreators()
    {
        static map<string, Creator> creators
        {
            {"card", []() -> Pay*
            {
                return new Card();
            }},

            {"paypal", []() -> Pay*
            {
                return new PayPal();
            }},

            {"crypto", []() -> Pay*
            {
                return new Crypto();
            }}
        };

        return creators;
    }


public:

    static Pay* create(string type)
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


class PayemntFactoryDemo {
public:
    void demo() {
        Pay* payment = PaymentFactory::create("paypal");

        if (payment)
        {
            payment->process();
        }

        delete payment;
    }
};
