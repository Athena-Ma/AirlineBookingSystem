// main.cpp : This file contains the "main" function. Program execution begins and ends here.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdio>
#include "Flight.h"
#include "User.h"
#include "Airport.h"
using namespace std;

bool checkInput(string _s, int _i);
bool checkInput(string _s);

int main(){
	// Input the information of each flight
	string data = "./flightInfo.txt";
	string account = "0";
	Airport airport(data);
	cout << "Welcome to " << airport.getName() << " airline booking system! " << endl;

	// Switch an order
	int order = -1;
	while (true) {
		cout << "Please choose a number: " << endl
			<< "\t1.Show all flights information " << endl
			<< "\t2.Query flights." << endl
			<< "\t3.Booking." << endl
			<< "\t4.Refund." << endl
			<< "\t0.Exit." << endl;
		string s;
		cin >> s;
		if (checkInput(s, 1)) order = stoi(s);

		// Information browsing of each flight
		if (order == 1) {
			airport.showFlights();
		}

		// Query flights
		else if (order == 2) {
			cout << endl;
			airport.queryFlight();
		}

		// Booking business
		else if (order == 3) {
			cout << "Please log in. (0 to return the last step )" << endl;
			cout << "Accont: ";
			cin >> account;
			if (account != "0") {
				User user(account);
				bool isLog = user.logIn();
				while (isLog) {
					user.showTicket();
					if (!user.bookTicket(airport))break;
				}
			}
		}

		// Refund business
		else if (order == 4) {
			cout << "Please log in. (0 to return the last step )" << endl;
			cout << "Accont: ";
			cin >> account;
			if (account == "0") break;
			User user(account);
			bool isLog = user.logIn();
			while (isLog) {
				user.showTicket();
				if (!user.refundTicket(airport))break;
			}
		}

		// Return last step
		else if (order == 0) {
			return 0;
		}
		cout << endl << endl << endl;
	}
}
