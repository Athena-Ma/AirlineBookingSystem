#include <string>
using namespace std;

bool checkInput(string _s, int _i) {
	bool ret = true;
	if (_s.size() <= _i) {
		for (int i = 0; i < _s.size(); i++) {
			if (_s[i] < '0' || _s[i] > '9')	ret = false;
		}
	}
	else return false;
	return ret;
}

bool checkInput(string _s) {
	bool ret = true;
	for (int i = 0; i < _s.size(); i++) {
		if (_s[i] > 'Z' || _s[i] < 'A') ret = false;
	}
	return ret;
}
