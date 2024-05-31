#include"Airport.h"
#include <fstream>

bool checkInput(string _s, int _i);
bool checkInput(string _s);

Airport::Airport(string _p) {
	path = _p;
	this->initialize();
}

void Airport::initialize() {
	v_flights.clear();
	ifstream infile;
	infile.open(path, ios::in);
	if (!infile.is_open()) {
		cout << "Data reading failure. " << endl;
	}
	Flight flight;
	while (infile >> flight) {
		v_flights.push_back(flight);
	}
	infile.close();
	name = v_flights[0].getStart();
}

void Airport::showFlights() {
	cout << "All flights information: " << endl;
	for (int i = 0; i < v_flights.size(); i++) {
		v_flights[i].print();
	}
}

void Airport::queryFlight() {
	bool flag = true;
	while (flag) {
		cout << "Please choose a type of query: " << endl
			<< "\t1.By flight ID." << endl
			<< "\t2.By departure time." << endl
			<< "\t3.By terminal station." << endl
			<< "\t0.Return last step." << endl;
		string s;
		cin >> s;
		cout << endl;
		int queryWay = -1;
		if (checkInput(s, 1)) queryWay = stoi(s);
		switch (queryWay) {
		case 1:  // query by flight ID
			while (true) {
				cout << "Please type in the flight ID. (0 to return the last step )" << endl << "ex.1234" << endl;
				cin >> s;
				int i_query = -1;
				if (checkInput(s, 4)) i_query = stoi(s);
				if (i_query == 0) break;
				bool flag1 = false;
				for (int i = 0; i < v_flights.size(); i++) {
					if (v_flights[i].queryFlight(i_query)) {
						flag1 = true;
						v_flights[i].print();
					}
				}
				if (!flag1) {
					cout << "No such flight. " << endl;
					flag1 = false;
				}
				cout << endl;
			}
			break;
		case 2:  // query by departure time
			while (flag) {
				cout << "Please type in the departure time. (0 to return the last step )" << endl << "ex.2024 06 07" << endl;
				cin >> s;
				int y, m, d;
				if (checkInput(s, 4))y = stoi(s);
				else continue;
				if (y == 0)	break;
				cin >> m >> d;
				Date* d_query = new Date(y, m, d);
				bool flag1 = false;
				for (int i = 0; i < v_flights.size(); i++) {
					if (v_flights[i].queryFlight(*d_query)) flag1 = true;
				}
				if (!flag1) {
					cout << "No such flight. " << endl;
					flag1 = false;
				}
				delete d_query;
				cout << endl;
			}
			break;
		case 3:  // query by terminal station
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			while (flag) {
				cout << "Please type in the terminal station. (0 to return the last step )" << endl << "ex.SHA" << endl;
				string s_query;
				getline(cin, s_query);
				if (s_query == "0") break;
				if (!checkInput(s_query)) s_query = "a";
				bool flag1 = false;
				for (int i = 0; i < v_flights.size(); i++) {
					if (v_flights[i].queryFlight(s_query)) flag1 = true;
				}
				if (!flag1) {
					cout << "No such flight. " << endl;
					flag1 = false;
				}
			}
			break;
		case 0:  // 0 to return last step
			flag = false;
			break;
		default:
			break;
		}
		cout << endl;
	}
}
