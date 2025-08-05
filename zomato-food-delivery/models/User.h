#ifndef USER_H
#define USER_H

#include <string>
#include "Cart.h"
using namespace std;

class User {
private:
    int userId;
    string name;
    string address;
    Cart* cart;
public:
    User(int _userId, string& _name, string& _address) {
        this->userId = _userId;
        this->name = _name;
        this->address = _address;
        cart = new Cart();
    }
    ~User() {
        delete cart;
    }
    string getName() {
        return name;
    }
    void setName(string& _name) {
        name = _name;
    }
    string getAddress() {
        return address;
    }
    void setAddress(string& _address) {
        address = _address;
    }
    Cart* getCart() {
        return cart;
    }
};

#endif // USER_H