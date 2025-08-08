#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Notification {
public:
    virtual string getContent() const = 0;

    virtual ~Notification() {}
};

// Concrete Notification: simple text notification.
class SimpleNotification : public Notification {
private:
    string text;
public:
    SimpleNotification(const string& msg) {
        text = msg;
    }
    string getContent() const override {
        return text;
    }
};

// Abstract Decorator: wraps a Notification object.
class NotificationDecorator : public Notification {
protected:
    Notification* notification;
public:
    NotificationDecorator(Notification* n) {
        notification = n;
    }
    virtual ~NotificationDecorator() {
        delete notification;
    }
};

// Decorator to add a timestamp to the content.
class TimestampDecorator : public NotificationDecorator {
public:
    TimestampDecorator(Notification* n) : NotificationDecorator(n) { }
    
    string getContent() const override {
        return "[2025-04-13 14:22:00] " + notification->getContent();
    }
};

// Decorator to append a signature to the content.
class SignatureDecorator : public NotificationDecorator {
private:
    string signature;
public:
    SignatureDecorator(Notification* n, const string& sig) : NotificationDecorator(n) {
        signature = sig;
    }
    string getContent() const override {
        return notification->getContent() + "\n-- " + signature + "\n\n";
    }
};

/*============================
  Observer Pattern Components
=============================*/

// Observer interface: each observer gets an update with a Notification pointer.
class Observer {
public:
    virtual void update() = 0;

    virtual ~Observer() {}
};

class Observable {
public:
    virtual void addObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

// Concrete Observable
class NotificationObservable :  public Observable {
private:
    vector<Observer*> observers;
    Notification* currentNotification;
public:
    NotificationObservable() { 
        currentNotification = nullptr; 
    }

    void addObserver(Observer* obs) override {
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs) override {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notifyObservers() override {
        for (unsigned int i = 0; i < observers.size(); i++) {
            observers[i]->update();
        }
    }

    void setNotification(Notification* notification) {
        if (currentNotification != nullptr) {
            delete currentNotification;
        }
        currentNotification = notification;
        notifyObservers();
    }

    Notification* getNotification() {
        return currentNotification;
    }

    string getNotificationContent() {
        return currentNotification->getContent();
    }

    ~NotificationObservable() {
        if (currentNotification != NULL) {
            delete currentNotification;
        }
    }
};

// The NotificationService manages notifications. It keeps track of notifications. 
// Any client code will interact with this service.

// Singleton class
class NotificationService {
private:
    NotificationObservable* observable;
    static NotificationService* instance;
    vector<Notification*> notifications;

    NotificationService() {
        // private constructor
        observable = new NotificationObservable();
    }

public:
    static NotificationService* getInstance() {
        if(instance == nullptr) {
            instance = new NotificationService();
        }
        return instance;
    }

    // Expose the observable so observers can attach.
    NotificationObservable* getObservable() {
        return observable;
    }

    // Creates a new Notification and notifies observers.
    void sendNotification(Notification* notification) {
        notifications.push_back(notification);
        observable->setNotification(notification);
    }

    ~NotificationService() {
        delete observable;
    }
};

NotificationService* NotificationService::instance = nullptr;

class Logger : public Observer {
private:
    NotificationObservable* notificationObservable;

public:
    Logger() {
       this->notificationObservable = NotificationService::getInstance()->getObservable();
       notificationObservable->addObserver(this);
    }

    Logger(NotificationObservable* observable) {
        this->notificationObservable = observable;
        notificationObservable->addObserver(this);
    }

    void update() {
        cout << "Logging New Notification : \n" << notificationObservable->getNotificationContent();
    }
};

// Abstract class for different Notification Strategies.
class NotificationStrategy {
public:    
    virtual void sendNotification(string content) = 0;
};

class EmailStrategy : public NotificationStrategy {
private:
    string emailId;
public:

    EmailStrategy(string emailId) {
        this->emailId = emailId;
    }

    void sendNotification(string content) override {
        // Simulate the process of sending an email notification, 
        // representing the dispatch of messages to users via email.​
        cout << "Sending email Notification to: " << emailId << "\n" << content;
    }
};

class SMSStrategy : public NotificationStrategy {
private:
    string mobileNumber;
public:

    SMSStrategy(string mobileNumber) {
        this->mobileNumber = mobileNumber;
    }

    void sendNotification(string content) override {
        // Simulate the process of sending an SMS notification, 
        // representing the dispatch of messages to users via SMS.​
        cout << "Sending SMS Notification to: " << mobileNumber << "\n" << content;
    }
};

class PopUpStrategy : public NotificationStrategy {
public:
    void sendNotification(string content) override {
        // Simulate the process of sending popup notification.
        cout << "Sending Popup Notification: \n" << content;
    }
};

class NotificationEngine : public Observer {
private:
    NotificationObservable* notificationObservable;
    vector<NotificationStrategy*> notificationStrategies;

public:
    NotificationEngine() {
        this->notificationObservable = NotificationService::getInstance()->getObservable();
        notificationObservable->addObserver(this);
    }

    NotificationEngine(NotificationObservable* observable) {
        this->notificationObservable = observable;
    }

    void addNotificationStrategy(NotificationStrategy* ns) {
        this->notificationStrategies.push_back(ns);
    }

    // Can have RemoveNotificationStrategy as well.

    void update() {
        string notificationContent = notificationObservable->getNotificationContent();
        for(const auto notificationStrategy : notificationStrategies) {
            notificationStrategy->sendNotification(notificationContent);
        }
    }
};

int main() {
    // Create NotificationService.
    NotificationService* notificationService = NotificationService::getInstance();
   
    // Create Logger Observer
    Logger* logger = new Logger();

    // Create NotificationEngine observers.
    NotificationEngine* notificationEngine = new NotificationEngine();

    notificationEngine->addNotificationStrategy(new EmailStrategy("random.person@gmail.com"));
    notificationEngine->addNotificationStrategy(new SMSStrategy("+91 9876543210"));
    notificationEngine->addNotificationStrategy(new PopUpStrategy());

    // Create a notification with decorators.
    Notification* notification = new SimpleNotification("Your order has been shipped!");
    notification = new TimestampDecorator(notification);
    notification = new SignatureDecorator(notification, "Customer Care");
    
    notificationService->sendNotification(notification);

    delete logger;
    delete notificationEngine;
    return 0;
}