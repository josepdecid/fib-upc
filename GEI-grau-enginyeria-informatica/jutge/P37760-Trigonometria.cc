#include <iostream>
#include <cmath>
using namespace std;


//Pre: Llegeix un angle en graus
//Post: Obtenim el sinus i cosinus
int main() {
	cout.setf(ios::fixed);
	cout.precision(6);
	double x;
	while (cin >> x) {
		x = (x*M_PI)/180;
		cout << sin(x) << ' ' << cos(x) << endl;
	}
}