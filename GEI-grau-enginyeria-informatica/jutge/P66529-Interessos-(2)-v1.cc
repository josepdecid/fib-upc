#include <iostream>
using namespace std;

//Programa usant una variable c;

int main() {
	cout.setf(ios::fixed);
	cout.precision(4);
	double i, c, aux;
	string t;
	cin >> i >> t;
	c = aux = 1000;
	if (t == "setmanal") {
		i = i/52;
		for (int j = 52; j != 0; --j) {
		c = c + c*(i/100);
	    }
	}else if (t == "mensual") {
		i = i/12;
		for (int j = 12; j != 0; --j) {
		c = c + c*(i/100);
	    }
	}else if (t == "trimestral") {
		i = i/4;
		for (int j = 4; j != 0; --j) {
		c = c + c*(i/100);
	    }
	}else if (t == "semestral") {
		i = i/2;
		for (int j = 2; j != 0; --j) {
		c = c + c*(i/100);
	    }
	} 
	cout << 100*(c-aux)/aux << endl;
}