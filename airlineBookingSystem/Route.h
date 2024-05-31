#pragma once
#include <string>
#include <string.h>
using namespace std;

class Route {
	string starting_station;
	string terminal_station;
public:
	Route() { starting_station = ""; terminal_station = ""; }
	Route(string _start, string _terminal) :starting_station(_start), terminal_station(_terminal) {}
	string getStart() const { return starting_station; }
	string getTerminal () const { return terminal_station; }
	void print();
	friend ostream& operator << (ostream& ost, Route& r);
	friend istream& operator >> (istream& ist, Route& r);
};
