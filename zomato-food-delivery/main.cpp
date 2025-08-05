#include <iostream>
#include "ZomatoApp.h"
using namespace std;

int main() {
    // Create ZomatoApp Object
    ZomatoApp* zomato = new ZomatoApp();

    // Simulate a user coming in (Happy Flow)
    string name = "Harshit";
    string location = "Chandigarh";
    User* user = new User(101, name, location);
    cout << "User: " << user->getName() << " is active." << endl;

    // User searches for restaurants by location
    vector<Restaurant*> restaurantList = zomato->searchRestaurants("Delhi");

    if (restaurantList.empty()) {
        cout << "No restaurants found!" << endl;
        return 0;
    }
    cout << "Found Restaurants:" << endl;
    for (auto restaurant : restaurantList) {
        cout << " - " << restaurant->getName() << endl;
    }

    // User selects a restaurant
    zomato->selectRestaurant(user, restaurantList[0]);

    cout << "Selected restaurant: " << restaurantList[0]->getName() << endl;

    // User adds items to the cart
    zomato->addToCart(user, "P1");
    zomato->addToCart(user, "P2");

    zomato->printUserCart(user);

    // User checkout the cart
    string mobile = "1234567890";
    Order* order = zomato->checkoutNow(user, "Delivery", new UPIPaymentStrategy(mobile));
    
    // User pay for the cart. If payment is success, notification is sent.
    zomato->payForOrder(user, order);

    // Cleanup Code.
    delete zomato;
    delete user;
    
    return 0;
}