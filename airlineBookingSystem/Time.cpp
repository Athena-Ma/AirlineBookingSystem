#include "Time.h"
#include <iomanip>
using namespace std;

bool operator==(const Date& d1, const Date& d2) {
	return (d1.getYear() == d2.getYear() && d1.getMonth() == d2.getMonth());
}

Date& Date::operator=(const Date& d) {
	this->year = d.year;
	this->month = d.month;
	this->day = d.day;
	return *this;
}

void Time::print() {
	cout << year << "."
		<< setfill('0') << setw(2) << right << month << "."
		<< setfill('0') << setw(2) << right << day << " "
		<< setfill('0') << setw(2) << right << hour << ": "
		<< setfill('0') << setw(2) << right << minute;
}

ostream& operator << (ostream& ost, Date& d) {
	ost << d.year << "."
		<< setfill('0') << setw(2) << right << d.month << "."
		<< setfill('0') << setw(2) << right << d.day;
	return ost;
}

istream& operator >> (istream& ist, Date& d) {
	ist >> d.year >> d.month >> d.day;
	return ist;
}

ostream& operator << (ostream& ost, Time& t) {
	ost << t.year << " "  << t.month << " " << t.day << " " << t.hour << " " << t.minute;
	return ost;
}

istream& operator >> (istream& ist, Time& t) {
	ist >> t.year >> t.month >> t.day >> t.hour >> t.minute;
	return ist;
}
