#ifndef ORDER_FACTORY_H
#define ORDER_FACTORY_H

#include<vector>
#include<string>
#include"../models/Order.h"
#include"../models/Cart.h"
#include"../models/Restaurant.h"
#include"../strategies/PaymentStrategy.h"
using namespace std;

class OrderFactory {
public:
    virtual Order* createOrder(User* _user, Cart* _cart, Restaurant* _restaurant, vector<MenuItem>& _menuItems, 
                                PaymentStrategy* _paymentStrategy, double _totalCost, string& _orderType) = 0;
    virtual ~OrderFactory() {}
};

#endif