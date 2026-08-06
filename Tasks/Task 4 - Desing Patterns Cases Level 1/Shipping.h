#pragma once
#include<iostream>
using namespace std;

//class Shipping
//{
//public:
//
//    double calculate(string type, double weight)
//    {
//        if (type == "air")
//        {
//            return weight * 10;
//        }
//
//        if (type == "truck")
//        {
//            return weight * 5;
//        }
//
//        if (type == "ship")
//        {
//            return weight * 2;
//        }
//
//        return 0;
//    }
//
//};

//Problem : Adding shipping methods requires modifying this class.
//
//Solution : Using Strategy Pattern


class ShippingStrategy
{
public:
    virtual double calculate(double weight) const = 0;
};

class AirShipping : public ShippingStrategy
{
public:
    double calculate(double weight) const override
    {
        return weight * 10;
    }
};

class TruckShipping : public ShippingStrategy
{
public:
    double calculate(double weight) const override
    {
        return weight * 5;
    }
};

class ShipShipping : public ShippingStrategy
{
public:
    double calculate(double weight) const override
    {
        return weight * 2;
    }
};


class Shipping
{
public:

    double calculate(ShippingStrategy* ship, double weight)
    {
        ship->calculate(weight);
    }
};