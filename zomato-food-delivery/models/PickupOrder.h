#ifndef PICKUP_ORDER_H
#define PICKUP_ORDER_H

#include "Order.h"
using namespace std;

class PickupOrder : public Order {
private:
    string restaurantAddress;

public:
    PickupOrder() {
        restaurantAddress = "";
    }

    string getType() override {
        return "Pickup";
    }

    void setRestaurantAddress(const string& addr) {
        restaurantAddress = addr;
    }

    string getRestaurantAddress() const {
        return restaurantAddress;
    }
};

#endif // PICKUP_ORDER_H