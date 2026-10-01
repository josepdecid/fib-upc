#include <iostream>
using namespace std;

//Pre: interés en tan per cent i períodes
//Post: TAE corresponent

int main() {
	cout.setf(ios::fixed);
	cout.precision (4);	
	double i, TAE, p;
 	string t;
 	cin >> i >> t;
 	if (t == "setmanal") p = 52;
 	else if (t == "mensual") p = 12;
 	else if (t == "trimestral") p = 4;
 	else if (t == "semestral") p = 2;
 	i = i/100;
 	i = i/p;
 	TAE = 1+i;
 	while (p != 1) {
		TAE = TAE*(1+i);
		--p;
	}
	cout << 100*(TAE-1) << endl;
}