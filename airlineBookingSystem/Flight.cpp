#include "Flight.h"
#include <iomanip>
using namespace std;

Flight::Flight() {

}

//Flight::Flight(int _flight, Route _route, Time _time, int _ticket) {
//	flight_ID = _flight;
//	route = _route;
//	time = _time;
//	ticket_number = _ticket;
//}

//Flight::Flight(int _flight, string _start, string _terminal, int _y, int _m, int _d, int _h, int _min, int ticket) {
//	flight_ID = _flight;
//	route.starting_station = _start;
//	route.terminal_station = _terminal;
//	
//}

int Flight::getFlightID() {
	return flight_ID;
}

Date Flight::getFlightDate() {
	return time;
}

string Flight::getTerminal() {
	return route.getTerminal();
}

bool Flight::queryFlight(int query) {
	if (this->getFlightID() == query) {
		return true;
	}
	return false;
}

bool Flight::queryFlight(Date query) {
	if (this->getFlightDate() == query) {
		cout << *this << endl;
		return true;
	}
	return false;
}

bool Flight::queryFlight(string query) {
	if (this->getTerminal() == query) {
		cout << *this << endl;
		return true;
	}
	return false;
}

ostream& operator << (ostream& ost, Flight& f) {
	ost << setw(4) << left << f.flight_ID << ": \t" << f.route << " \t" << f.time << "\tticket: " << setfill(' ') << setw(3) << right << f.ticket_number;
	return ost;
}

istream& operator >> (istream& ist, Flight& f) {
	ist >> f.flight_ID >> f.route >> f.time >> f.ticket_number;
	return ist;
}

