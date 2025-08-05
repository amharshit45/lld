#ifndef CREDIT_CARD_PAYMENT_STRATEGY_H
#define CREDIT_CARD_PAYMENT_STRATEGY_H

#include<iostream>
#include<string>
#include"PaymentStrategy.h"

class CreditCardPaymentStrategy: public PaymentStrategy {
private:
    string cardNumber;
public:
    CreditCardPaymentStrategy(string& _cardNumber) {
        this -> cardNumber = _cardNumber;
    }
    void pay(double amount) override {
        cout << "Paid $" << amount << " using Credit Card [" << cardNumber << "]\n";
    }
};

#endif // CREDIT_CARD_PAYMENT_STRATEGY_H