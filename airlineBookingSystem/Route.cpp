#include "Route.h"
#include <iostream>
using namespace std;

void Route::print() {
	cout << starting_station + " --> " << terminal_station;
}

ostream& operator << (ostream& ost, Route& r) {
	ost << r.starting_station << " " << r.terminal_station;
	return ost;
}

istream& operator >> (istream& ist, Route& r) {
	ist >> r.starting_station >> r.terminal_station;
	return ist;
}
