#pragma once
#include "Route.h"
#include "Time.h"

class Flight {
	int flight_ID;
	Route route;
	Time time;
	int ticket_number;
public:
	Flight();
	//Flight(int _flight, Route _route, Time _time, int _ticket);
	Flight(int _flight, string _start, string _terminal, int _y, int _m, int _d, int _h, int _min, int ticket);
	int getFlightID();
	Date getFlightDate();
	string getTerminal();
	int getFlightTicket() { return ticket_number; }
	bool queryFlight(int query);
	bool queryFlight(Date query);
	bool queryFlight(string query);
	void bookTicket(int number) { if (number <= ticket_number) ticket_number -= number; }
	friend ostream& operator << (ostream& ost, Flight& t);
	friend istream& operator >> (istream& ist, Flight& t);
};
