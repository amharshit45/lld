#ifndef CART_H
#define CART_H

#include<iostream> 
#include<vector>
#include<string>
#include"../models/MenuItem.h"
#include"../models/Restaurant.h"

class Cart {
private:
    Restaurant* restaurant;
    vector<MenuItem> cartItems;
    double totalPrice;
public:
    Cart() {
        restaurant = nullptr;
        totalPrice = 0;
    }
    void setRestaurant(Restaurant* _restaurant) {
        restaurant = _restaurant;
    }
    Restaurant* getRestaurant() {
        return restaurant;
    }
    void addItemToCart(MenuItem& _item) {
        if (!restaurant) {
            cout << "Set restaurant before adding items to cart.\n";
            return;
        }
        cartItems.push_back(_item);
        totalPrice += _item.getPrice();
    }
    vector<MenuItem>& getCart() {
        return cartItems;
    }
    double getTotalCost() {
        return totalPrice;
    }
    bool isEmpty() {
        return !restaurant || cartItems.empty();
    }
    void clear() {
        restaurant = nullptr;
        cartItems.clear();
        totalPrice = 0;
    }
};

#endif // CART_H