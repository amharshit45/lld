#ifndef UPI_PAYMENT_STRATEGY_H
#define UPI_PAYMENT_STRATEGY_H

#include<iostream>
#include<string>
#include"PaymentStrategy.h"

class UPIPaymentStrategy: public PaymentStrategy {
private:
    string mobile;
public:
    UPIPaymentStrategy(string& _mobile) {
        this -> mobile = _mobile;
    }
    void pay(double amount) override {
        cout << "Paid $" << amount << " using UPI [" << mobile << "]\n";
    }
};

#endif // UPI_PAYMENT_STRATEGY_H