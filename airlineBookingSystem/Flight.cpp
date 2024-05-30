#include "Flight.h"
#include <iomanip>
using namespace std;

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

