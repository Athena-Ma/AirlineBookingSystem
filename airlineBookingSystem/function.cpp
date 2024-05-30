#include <string>
using namespace std;

bool checkInput(string s, int x) {
	bool ret = true;
	if (s.size() <= x) {
		for (int i = 0; i < s.size(); i++) {
			if (s[i] < '0' || s[i] > '9')	ret = false;
		}
	}
	else return false;
	return ret;
}

bool checkInput(string s) {
	bool ret = true;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] > 'Z' || s[i] < 'A') ret = false;
	}
	return ret;
}
