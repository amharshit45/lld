#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<iostream>
#include<string>
#include<vector>
#include"MenuItem.h"

class Restaurant {
private:
    static int nextRestaurantID;
    int restaurantID;
    string name;
    string location;
    vector<MenuItem> menu;
public:
    Restaurant (string& _name, string& _location) {
        this -> name = _name;
        this -> location = _location;
        this -> restaurantID = ++nextRestaurantID;
    } 
    ~Restaurant() {
        cout << "Deleting Restaurant \"" << name << "\" and clearing its menu.\n";
        menu.clear();
    }
    string getName() {
        return name;
    }
    void setName(string& _name) {
        name = _name;
    }
    string getLocation() {
        return location;
    }
    void setLocation(string& _location) {
        location = _location;
    }
    vector<MenuItem>& getMenu() {
        return menu;
    }
    void addMenuItem(MenuItem& _item) {
        menu.push_back(_item);
    }
};

int Restaurant::nextRestaurantID = 0;

#endif // RESTAURANT_H