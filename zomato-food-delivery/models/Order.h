#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "Restaurant.h"
#include "MenuItem.h"
#include "../strategies/PaymentStrategy.h"
#include "../utils/TimeUtils.h"
using namespace std;

class Order {
protected:
    static int nextOrderId;
    int orderId;
    User* user;
    Restaurant* restaurant;
    vector<MenuItem> items;
    PaymentStrategy* paymentStrategy;
    double total;
    string scheduled;

public:
    Order() {
        user = nullptr;
        restaurant = nullptr;
        paymentStrategy = nullptr;
        total = 0.0;
        scheduled = "";
        orderId = ++nextOrderId;
    }

    virtual ~Order() {
        delete paymentStrategy;
    }

    bool processPayment() {
        if (paymentStrategy) {
            paymentStrategy -> pay(total);
            return true;
        } else {
            cout << "Please choose a payment mode first.\n";
            return false;
        }
    }

    virtual string getType() = 0;

    int getOrderId() {
        return orderId;
    }

    void setUser(User* _user) {
        user = _user;
    }

    User* getUser() {
        return user;
    }

    void setRestaurant(Restaurant* _restaurant) {
        restaurant = _restaurant;
    }

    Restaurant* getRestaurant() {
        return restaurant;
    }

    void setItems(vector<MenuItem>& _items) {
        items = _items;
        total = 0;
        for (auto &i : items) {
            total += i.getPrice();
        }
    }

    vector<MenuItem>& getItems() {
        return items;
    }

    void setPaymentStrategy(PaymentStrategy* _paymentStrategy) {
        paymentStrategy = _paymentStrategy;
    }

    void setScheduled(string& s) {
        scheduled = s;
    }

    string getScheduled() {
        return scheduled;
    }

    double getTotal() {
        return total;
    }

    void setTotal(int _total) {
        this->total = _total;
    }
};

int Order::nextOrderId = 0;

#endif // ORDER_H