#include <fstream>
#include <iomanip>
#include "User.h"
#include "Airport.h"

bool checkInput(string _s, int _i);
bool checkInput(string _s);

int User::logIn() {
	string filename;
	filename = "./account/" + userName + ".txt";
	ifstream ifile;
	ifile.open(filename, ios::in);
	if (!ifile.is_open()) {
		cout << "Creating a new account " << userName << " ." << endl;
		cout << "Please set your password: ";
		string p;
		cin >> p;
		password = p;
		ofstream outputFile(filename);
		outputFile << p << endl;
		outputFile.close();
		ifile.open(filename, ios::in);
		cout << "New acount created successfully." << endl;
		ifile.close();
	}
	else {
		cout << "Welcome back, " << userName << "." << endl;
		int cnt = 0;
		while (cnt <= 5) {
			cout << "Please type in your pasword : ";
			string p;
			cin >> p;
			string line;
			getline(ifile, line);
			ifile.close();
			if (p != line) {
				cnt++;
				cout << "Password wrong. Do you want to type again? [y/n]" << endl;
				string s;
				cin >> s;
				if (s != "y" && s != "Y")return 0;
			}
			else {
				ifile.open(filename, ios::in);
				getline(ifile, line);
				while (getline(ifile, line)) {
					flights.push_back(make_pair<int, int>(stoi(line.substr(0, 4)), stoi(line.substr(6, 8))));
				}
				break;
			}
		}
		if (cnt > 5) {
			cout << "Wrong pasword too many times!" << endl;
			return 0;
		}
	}
	cout << "Hello, " << userName << endl;
	return 1;
}

void User::showTicket() {
	cout << "Your ticket: " << endl;
	bool isTicket = false;  // Is any ticket exist
	string filename;
	filename = "./account/" + userName + ".txt";
	ifstream ifile;
	ifile.open(filename, ios::in);
	string line;
	getline(ifile, line);
	while (getline(ifile, line)) {
		cout << line << endl;
		isTicket = true;
	}
	if (!isTicket) cout << "None." << endl;
}

bool User::bookTicket(Airport& a) {
	cout << "Please type in the flight ID." << endl;
	string s;
	cin >> s;
	cout << endl;
	int i_query = -1;
	if (checkInput(s, 4)) i_query = stoi(s);
	else i_query = -1;
	if (i_query == 0) return false;
	bool flag1 = false;  // Is there any flight ID is the same
	string filename;
	filename = "./account/" + userName + ".txt";
	ifstream ifile;
	vector<Flight> v_flight = a.getFlights();
	for (int i = 0; i < v_flight.size(); i++) {
		if (v_flight[i].queryFlight(i_query)) {
			flag1 = true;
			cout << "You are booking this flight: " << endl;
			v_flight[i].print();
			cout << "Booking number: ";
			cin >> s;
			int number = 0;
			if (checkInput(s, 3)) number = stoi(s);
			if (number == 0) break;
			if (number <= v_flight[i].getFlightTicket()) {
				string tempFilename = "./account/" + userName + "_temp.txt";
				ofstream ofile(tempFilename);
				if (!ofile.is_open()) {
					cout << "Failed to writing." << endl;
					break;
				}
				v_flight[i].bookTicket(number);
				bool flag2 = false;  // Is the user already have this flight's ticket
				ifile.close();
				ifile.open(filename, ios::in);
				string line;
				while (getline(ifile, line)) {
					if (line.substr(0, 4) == to_string(v_flight[i].getFlightID())) {
						ofile << v_flight[i].getFlightID() << " " << setfill(' ') << setw(3) << right << stoi(line.substr(6, 8)) + number << endl;
						flag2 = true;
					}
					else {
						ofile << line << endl;
					}
				}
				if (!flag2) {
					ofile << v_flight[i].getFlightID() << " " << setfill(' ') << setw(3) << right << number;
				}
				ifile.close();
				ofile.close();
				remove(filename.c_str());
				if (rename(tempFilename.c_str(), filename.c_str()) == -1) cout << "Error." << endl;
				cout << "Book sucessfully." << endl;
				string temp = "./temp.txt";
				ofstream oInfoFile(temp);
				for (int j = 0; j < v_flight.size(); j++) {
					oInfoFile << v_flight[j] << endl;
				}
				oInfoFile.close();
				string path = "./flightInfo.txt";
				remove(path.c_str());
				if (rename(temp.c_str(), path.c_str()) == -1) cout << "Error." << endl;
				a.initialize();
				break;
			}
			else {
				cout << "No enough tickets!" << endl;
				ifile.close();
				break;
			}
		}
	}
	if (!flag1) {
		cout << "No such flight. " << endl;
		flag1 = false;
	}
	ifile.close();
	return true;
}

bool User::refundTicket(Airport& a) {
	cout << "Please type in the flight ID." << endl;
	string s;
	cin >> s;
	int i_query = -1;
	if (checkInput(s, 4)) i_query = stoi(s);
	if (i_query == 0) return false;
	string filename;
	filename = "./account/" + userName + ".txt";
	ifstream ifile;
	ifile.open(filename);
	bool flag4 = false;  // Is such flight.
	bool flag5 = false;  // Is refund sucesseed.
	bool flag6 = true;  // Is ticket enough
	int number;
	cout << endl;
	string line;
	vector<Flight> v_flight = a.getFlights();
	while (getline(ifile, line)) {
		if (line.substr(0, 4) == to_string(i_query)) {
			flag4 = true;
			cout << "You are refunding this flight:" << endl;
			for (int i = 0; i < v_flight.size(); i++) {
				if (v_flight[i].getFlightID() == i_query) v_flight[i].print();
			}
			cout << "Number: ";
			cin >> s;
			cout << endl;
			if (checkInput(s, 3))number = stoi(s);
			if (number > stoi(line.substr(6, 8))) {
				cout << "No enough tickets. " << endl;
				flag6 = false;
			}
			else {
				flag5 = true;
			}
			break;
		}
	}
	ifile.close();
	if (!flag4) {
		cout << "No such flight. " << endl;
	}
	else if (flag6) {
		string tempFilename = "./account/" + userName + "_temp.txt";
		ofstream ofile(tempFilename);
		if (!ofile.is_open()) {
			cout << "Failed to writing." << endl;
			return false;
		}
		for (int i = 0; i < v_flight.size(); i++) {
			if (i_query == v_flight[i].getFlightID()) {
				v_flight[i].bookTicket(-number);
			}
		}
		ifile.open(filename, ios::in);
		string line;
		while (getline(ifile, line)) {
			if (line.substr(0, 4) == to_string(i_query)) {
				if (stoi(line.substr(6, 8)) == number) continue;
				ofile << i_query << " " << setfill(' ') << setw(3) << right << stoi(line.substr(6, 8)) - number << endl;
			}
			else {
				ofile << line << endl;
			}
		}
		ifile.close();
		ofile.close();
		remove(filename.c_str());
		if (rename(tempFilename.c_str(), filename.c_str()) == -1) cout << "Error." << endl;
		cout << "Refund sucessfully." << endl;
		ifile.close();
		string temp = "./temp.txt";
		ofstream oInfoFile(temp);
		for (int j = 0; j < v_flight.size(); j++) {
			oInfoFile << v_flight[j] << endl;
		}
		oInfoFile.close();
		remove(a.getPath().c_str());
		if (rename(temp.c_str(), a.getPath().c_str()) == -1)cout << "Error." << endl;
		a.initialize();
	}
}