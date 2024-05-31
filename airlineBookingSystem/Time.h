#pragma once
#include <iostream>
using namespace std;

class Date {
protected:
	int year;
	int month;
	int day;
public:
	Date() { year = 0; month = 1; day = 1; };
	Date(int _y, int _m, int _d) :year(_y), month(_m), day(_d) {};
	int getYear()const { return year; }
	int getMonth()const { return month; }
	int getDay()const { return day; }
	Date& operator= (const Date& d);
	friend ostream& operator << (ostream& ost, Date& d);
	friend istream& operator >> (istream& ist, Date& d);
};
bool operator==(const Date& d1, const Date& d2);

class Time : public Date{
	int hour;
	int minute;
public:
	Time() { hour = 0; minute = 0; };
	Time(int _y, int _m, int _d, int _h, int _min) :Date(_y, _m, _d), hour(_h), minute(_min) {};
	int getHour()const { return hour; }
	int getMinute()const { return minute; }
	void print();
	friend ostream& operator << (ostream& ost, Time& t);
	friend istream& operator >> (istream& ist, Time& t);
};
