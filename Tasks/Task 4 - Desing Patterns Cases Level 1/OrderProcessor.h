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
// 
//SOLUTION : Using Strategy Pattern.


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