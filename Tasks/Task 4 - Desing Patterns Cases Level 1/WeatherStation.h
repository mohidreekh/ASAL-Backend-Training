#pragma once
#include <iostream>
#include<vector>
using namespace std;

//class WeatherStation
//{
//public:
//    void updateTemperature(int temp)
//    {
//        cout << "Temperature changed\n";
//        MobileApp app;
//        EmailService email;
//        Display display;
//        app.update(temp);
//        email.update(temp);
//        display.update(temp);
//    }
//};


//Problem : The Wither is tightly coupled on services 
// 
//SOLUTION : Using Observer patterns.



class Notifier {
public:
	virtual void update() = 0;
};

class MobileApp : public Notifier {
	void update() {
		cout << "Mobile App Update" << endl;
	}
};

class EmailService : public Notifier {
	void update() {
		cout << "Email Update" << endl;
	}

};

class Device : public Notifier {
	void update() {
		cout << "Device Update" << endl;
	}

};


class NotificationManager {
private:
	vector<Notifier*> _notifiers;
public:
	void subscribe(Notifier* notifier) {
		_notifiers.push_back(notifier);
	}

	void unsubscribe(Notifier* notifier) {
		_notifiers.erase(
			remove(_notifiers.begin(), _notifiers.end(), notifier),
			_notifiers.end()
		);
	}

	void notify() {
		for (Notifier* n: _notifiers)
		{
			n->update();
		}
	}

};