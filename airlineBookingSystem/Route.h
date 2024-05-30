#pragma once
#include <string>
#include <string.h>
using namespace std;

class Route {
	int route_ID;
	string starting_station;
	string terminal_station;
public:
	Route();
	Route(string _start, string _terminal);
	string getTerminal () const { return terminal_station; }
	friend ostream& operator << (ostream& ost, Route& r);
	friend istream& operator >> (istream& ist, Route& r);
};
