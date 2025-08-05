#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H

#include <vector>
#include <string>
#include <algorithm>
#include "../models/Restaurant.h"
using namespace std;

class RestaurantManager {
private:
    vector<Restaurant*> restaurants;
    static RestaurantManager* instance;
    RestaurantManager() {}
public:
    static RestaurantManager* getInstance() {
        if (!instance) {
            instance = new RestaurantManager();
        }
        return instance;
    }
    void addRestaurant(Restaurant* r) {
        restaurants.push_back(r);
    }
    vector<Restaurant*> searchByLocation(string _location) {
        vector<Restaurant*> result;
        transform(_location.begin(), _location.end(), _location.begin(), ::tolower);
        for (auto r : restaurants) {
            string _restaurantLocation = r->getLocation();
            transform(_restaurantLocation.begin(), _restaurantLocation.end(), _restaurantLocation.begin(), ::tolower);
            if (_restaurantLocation == _location) {
                result.push_back(r);
            }
        }
        return result;
    }
};

RestaurantManager* RestaurantManager::instance = nullptr;

#endif // RESTAURANT_MANAGER_H