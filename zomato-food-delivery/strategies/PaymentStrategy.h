#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H

#include<iostream>
using namespace std;

class PaymentStrategy {
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() {}
};

#endif // PAYMENTSTRATEGY_H