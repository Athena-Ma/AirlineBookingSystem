#pragma once
#include <vector>
#include "Flight.h"

class Airport {
	string name;
	vector<Flight> v_flights;
	string path;
public:
	Airport(string _p);
	string getName() const { return name; }
	string getPath() const { return path; }
	vector<Flight> getFlights() const { return v_flights; }
	void showFlights();
	void initialize();
	void queryFlight();
	~Airport(){}
};