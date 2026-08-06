#pragma once
#include<iostream>
using namespace std;

class OldPaymentGateway
{
public:

    void payInCents(int amount)
    {
        cout << "Paid "
            << amount
            << " cents\n";
    }
};

//class ShoppingCart
//{
//public:
//
//    void checkout(double amount)
//    {
//        OldPaymentGateway gateway;
//
//        gateway.payInCents(
//            amount * 100
//        );
//    }
//};

//Problem : ShoppingCart depends directly on old API.
//***********************
//Solution : using adpter pattern


class PaymentGatewayAdapter {
public:
    void payInDollar(int amount) 
    {
        OldPaymentGateway gateway;
        gateway.payInCents(amount * 100);
    }
};


class ShoppingCart
{
public:

    void checkout(double amount)
    {
        PaymentGatewayAdapter gateway;
        gateway.payInDollar(amount);
    }
};
