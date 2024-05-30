#pragma once
#include <iostream>
using namespace std;

class Date {
protected:
	int year;
	int month;
	int day;
public:
	Date() {};
	Date(int _y, int _m, int _d) :year(_y), month(_m), day(_d) {};
	int getYear()const { return year; }
	int getMonth()const { return month; }
	int getDay()const { return day; }
	Date& operator=(const Date& d);
	friend ostream& operator << (ostream& ost, Date& d);
	friend istream& operator >> (istream& ist, Date& d);
};
bool operator==(const Date& d1, const Date& d2);

class Time : public Date{
	int hour;
	int minute;
public:
	Time() {};
	Time(int _y, int _m, int _d, int _h, int _min) :Date(_y, _m, _d), hour(_h), minute(_min) {};
	friend ostream& operator << (ostream& ost, Time& t);
	friend istream& operator >> (istream& ist, Time& t);
};
