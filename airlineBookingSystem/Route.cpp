#include "Route.h"
#include <iostream>
using namespace std;

Route::Route() {

}

Route::Route(string _start, string _terminal){
	starting_station = _start;
	terminal_station = _terminal;
}

ostream& operator << (ostream& ost, Route& r) {
	ost << r.starting_station + " --> " << r.terminal_station;
	return ost;
}

istream& operator >> (istream& ist, Route& r) {
	ist >> r.starting_station >> r.terminal_station;
	return ist;
}
