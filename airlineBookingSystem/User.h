#pragma once
#include <vector>
#include "Flight.h"
#include "Airport.h"

class User {
	string userName;
	string password;
	vector<pair<int, int>> flights;
public:
	User(string _s) : userName(_s) {}
	int logIn();
	void showTicket();
	bool bookTicket(Airport& a);
	bool refundTicket(Airport& a);
};