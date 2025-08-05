#ifndef MENUITEM_H
#define MENUITEM_H

#include<string>
using namespace std;

class MenuItem {
private: 
    string code;
    string name;
    int price;
public:
    MenuItem(string& _code, string& _name, int _price) {
        this -> code = _code;
        this -> name = _name;
        this -> price = _price;
    }
    string getCode() {
        return code;
    }
    void setCode(string& _code) {
        code = _code;
    }
    string getName() {
        return name;
    }
    void setName(string& _name) {
        name = _name;
    }
    int getPrice() {
        return price;
    }
    void setPrice(int _price) {
        price = _price;
    }
};

#endif // MENUITEM_H