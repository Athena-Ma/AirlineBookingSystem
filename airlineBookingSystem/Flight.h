#pragma once
#include "Route.h"
#include "Time.h"

class Flight {
	int flight_ID;
	Route route;
	Time time;
	int ticket_number;
public:
	Flight() { flight_ID = -1;ticket_number = 0;}
	int getFlightID() const{ return flight_ID;};
	Date getFlightDate() const { return time;};
	string getStart() const { return route.getStart(); }
	string getTerminal() const { return route.getTerminal(); }
	int getYear() const { return time.getYear(); }
	int getMonth() const { return time.getMonth(); }
	int getDay() const { return time.getDay(); }
	int getHour() const { return time.getHour(); }
	int getMinute()const { return time.getMinute(); }
	int getTicketNumber()const { return ticket_number; }
	int getFlightTicket() const { return ticket_number; }
	bool queryFlight(int query);
	bool queryFlight(Date query);
	bool queryFlight(string query);
	void bookTicket(int number) { if (number <= ticket_number) ticket_number -= number; }
	void print();
	friend ostream& operator << (ostream& ost, Flight& t);
	friend istream& operator >> (istream& ist, Flight& t);
};
