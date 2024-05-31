#pragma once
#include <vector>
#include "Flight.h"

class Airport {
	string name;
	vector<Flight> v_flights;
	string path;
public:
	Airport(string _p);
	void initialize();
	string getName() { return name; }
	string getPath() { return path; }
	void showFlights();
	vector<Flight> getFlights() { return v_flights; }
	void queryFlight();
};