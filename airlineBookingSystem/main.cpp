// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdio>
#include "Flight.h"
using namespace std;
bool checkInput(string s, int i);
bool checkInput(string s);

int main(){
	cout << "Welcome! " << endl;
	ifstream infile;
	ifstream ifile;
	string account = "0";
	string filename;
	vector<Flight> v_flight;
	string path = "./flightInfo.txt";
	infile.open(path, ios::in);
	if (!infile.is_open()){
		cout << "Data reading failure. " << endl;
		return -1;
	}
	Flight flight;
	while (infile>>flight) {
		v_flight.push_back(flight);
	}
	infile.close();
	int order = -1;
	while (true) {
		cout << "Please choose a servise: " << endl
			<< "\t1.Show all flights information " << endl
			<< "\t2.Query flights." << endl
			<< "\t3.Booking." << endl
			<< "\t4.Refund." << endl
			<< "\t0.Exit." << endl;
		string s1;
		cin >> s1;
		if (checkInput(s1, 1))order = stoi(s1);
		int order2 = -1;
		bool flag;
		bool flag1;
		int i_query = -1;
		string s_query;
		Date* d_query;
		int y, m, d;
		if (order == 1) {
			cout << "All flights information: " << endl;
			for (int i = 0; i < v_flight.size(); i++) {
				cout << v_flight[i] << endl;
			}
		}
		else if (order == 2) {
			flag = true;
			cout << endl;
			while (flag) {
				cout << "Please choose a type of query: " << endl
					<< "\t1.By flight ID." << endl
					<< "\t2.By departure time." << endl
					<< "\t3.By terminal station." << endl
					<< "\t0.Return last step." << endl;
				string s2;
				cin >> s2;
				cout << endl;
				if (checkInput(s2, 1))order2 = stoi(s2);
				switch (order2) {
				case 1:
					while (true) {
						cout << "Please type in the flight ID. (0 to return the last step )" << endl
							<< "ex.1234" << endl;
						string s;
						cin >> s;
						if (checkInput(s, 4))i_query = stoi(s);
						if (i_query == 0) break;
						flag1 = false;
						for (int i = 0; i < v_flight.size(); i++) {
							if (v_flight[i].queryFlight(i_query)) {
								flag1 = true;
								cout << v_flight[i]<<endl;
							}
						}
						if (!flag1) {
							cout << "No such flight. " << endl;
							flag1 = false;
						}
						cout << endl;
					}
					break;
				case 2:
					while (flag) {
						cout << "Please type in the departure time. (0 to return the last step )" << endl
							<< "ex.2024 06 07" << endl;
						string s;
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						getline(cin, s);
						if (checkInput(s, 4))y = stoi(s);
						else continue;
						if (y == 0)	break;
						cin >> m >> d;
						d_query = new Date(y, m, d);
						flag1 = false;
						for (int i = 0; i < v_flight.size(); i++) {
							if (v_flight[i].queryFlight(*d_query)) flag1 = true;
						}
						if (!flag1) {
							cout << "No such flight. " << endl;
							flag1 = false;
						}
						delete d_query;
						cout << endl;
					}
					break;
				case 3:
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					while (flag) {
						cout << "Please type in the terminal station. (0 to return the last step )" << endl
							<< "ex.SHA" << endl;
						getline(cin, s_query);
						if (s_query == "0") break;
						if (!checkInput(s_query)) s_query = "aaa";
						flag1 = false;
						for (int i = 0; i < v_flight.size(); i++) {
							if (v_flight[i].queryFlight(s_query)) flag1 = true;
						}
						if (!flag1) {
							cout << "No such flight. " << endl;
							flag1 = false;
						}
					}
					break;
				case 0:
					flag = false;
					break;
				default:
					break;
				}
				cout << endl;
			}
		}
		else if (order == 3) {
			cout << "Please log in. (0 to return the last step )" << endl;
			cout << "Accont: ";
			cin >> account;
			if (account == "0") break;
			filename = "./" + account + ".txt";
			ifile.open(filename, ios::in);
			if (!ifile.is_open()) {
				ofstream outputFile(filename);
				ifile.open(filename, ios::in);
				outputFile.close();
			}
			ifile.close();
			cout << "Hello, " << account << endl;
			flag = true;
			while (flag) {
				string line;
				cout << "Your ticket: " << endl;
				bool flag3 = false;
				ifile.open(filename);
				while (getline(ifile, line)) {
					cout << line << endl;
					flag3 = true;
				}
				if (!flag3) {
					cout << "None." << endl;
				}
				cout<<"Please type in the flight ID." << endl;
				string s;
				cin >> s;
				if (checkInput(s, 4)) i_query = stoi(s);
				else i_query = -1;
				if (i_query == 0) break;
				flag1 = false;
				for (int i = 0; i < v_flight.size(); i++) {
					if (v_flight[i].queryFlight(i_query)) {
						flag1 = true;
						cout << "You are booking this flight: " << endl;
						cout << v_flight[i] << endl;
						cout << "Number: ";
						int number = 0;
						string s;
						cin >> s;
						if(checkInput(s, 3))number = stoi(s);
						if (number == 0) break;
						if (number <= v_flight[i].getFlightTicket()) {
							string tempFilename = "./" + account + "_temp.txt";
							ofstream ofile(tempFilename);
							if (!ofile.is_open()) {
								cout << "Failed to writing." << endl;
								break;
							}
							v_flight[i].bookTicket(number);	
							string line;
							bool flag2 = false;
							ifile.close();
							ifile.open(filename, ios::in);
							while (getline(ifile, line)) {
								if (line.substr(0, 4) == to_string(v_flight[i].getFlightID())) {
									ofile << v_flight[i].getFlightID() << " " << setfill(' ') << setw(3) << right << stoi(line.substr(6, 8))+number;
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
							if (rename(tempFilename.c_str(), filename.c_str())==-1)cout << "Error." << endl;
							cout << "Book sucessfully." << endl;
							ifile.close();
							string temp = "./temp.txt";
							ofstream oInfoFile(temp);
							for (int j = 0; j < v_flight.size(); j++) {
								oInfoFile << v_flight[j] << endl;
							}
							oInfoFile.close();
							remove(path.c_str());
							if (rename(temp.c_str(), path.c_str())==-1)cout << "Error." << endl;
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
			}
		}
		else if (order == 4) {
			cout << "Please log in. (0 to return the last step )" << endl;
			cout << "Accont: ";
			cin >> account;
			if (account == "0") break;
			filename = "./" + account + ".txt";
			ifile.open(filename, ios::in);
			if (!ifile.is_open()) {
				ofstream outputFile(filename);
				ifile.open(filename, ios::in);
				outputFile.close();
			}
			ifile.close();
			cout << "Hello, " << account << endl;
			flag = true;
			while (flag) {
				string line;
				cout << "Your ticket: " << endl;
				bool flag3 = false;
				ifile.open(filename);
				while (getline(ifile, line)) {
					cout << line << endl;
					flag3 = true;
				}
				if (!flag3) {
					cout << "None." << endl;
				}
				ifile.close();
				cout << "Please type in the flight ID." << endl;
				string s;
				cin >> s;
				if (checkInput(s, 4))i_query = stoi(s);
				if (i_query == 0) break;
				ifile.open(filename);
				bool flag4 = false;  // Is such flight.
				bool flag5 = false;  // Is refund sucesseed.
				bool flag6 = true;  // Is ticket enough
				int number;
				cout << endl;
				while (getline(ifile, line)) {
					if (line.substr(0, 4) == to_string(i_query)) {
						flag4 = true;
						cout << "You are refunding this flight:" << endl;
						cout << line << endl;
						cout << "Number: ";
						string s;
						cin >> s;
						cout << endl;
						if (checkInput(s,3))number = stoi(s);
						if (number > stoi(line.substr(6, 8)) ){
							cout<<"No enough tickets. "<<endl;
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
				else if(flag6){
					string tempFilename = "./" + account + "_temp.txt";
					ofstream ofile(tempFilename);
					if (!ofile.is_open()) {
						cout << "Failed to writing." << endl;
						break;
					}
					for (int i = 0; i < v_flight.size(); i++) {
						if (i_query == v_flight[i].getFlightID()) {
							v_flight[i].bookTicket(-number);
						}
					}
					string line;
					ifile.close();
					ifile.open(filename, ios::in);
					while (getline(ifile, line)) {
						if (line.substr(0, 4) == to_string(i_query) ){
							if (stoi(line.substr(6, 8)) - number == 0) continue;
							ofile << i_query << " " << setfill(' ') << setw(3) << right << stoi(line.substr(6, 8)) - number;
						}
						else {
							ofile << line << endl;
						}
					}
					ifile.close();
					ofile.close();
					remove(filename.c_str());
					if (rename(tempFilename.c_str(), filename.c_str())==-1)cout << "Error." << endl;
					cout << "Refund sucessfully." << endl;
					ifile.close();
					string temp = "./temp.txt";
					ofstream oInfoFile(temp);
					for (int j = 0; j < v_flight.size(); j++) {
						oInfoFile << v_flight[j].getFlightID() << " "
							<< v_flight[j].getStart() << " "
							<< v_flight[j].getTerminal() << " "
							<< v_flight[j].getYear() << " "
							<< v_flight[j].getMonth() << " "
							<< v_flight[j].getDay() << " "
							<< v_flight[j].getHour() << " "
							<< v_flight[j].getMinute() << " "
							<< v_flight[j].getTicketNumber() << endl;
					}
					oInfoFile.close();
					remove(path.c_str());
					if (rename(temp.c_str(), path.c_str())==-1)cout << "Error." << endl;
				}
			}
		}
		else if (order == 0) {
			return 0;
		}
		cout << endl << endl << endl;
	}
	return 0;
}
