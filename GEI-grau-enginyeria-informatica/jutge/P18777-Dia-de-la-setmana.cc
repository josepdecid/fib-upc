#include <iostream>
using namespace std;


//Pre: Llegeix una data
//Post: Sabem el dia de la setmana
string dia_de_la_setmana(int d, int m, int a) {
	int c, y, f;
	m = m - 2;
	if (m <= 0) {
		m = m + 12;
		--a;
	}
	c = a/100;
	y = a%100;
	f = ((2.6 * m) - 0.2);
	f= f + d + y + (y / 4) + (c / 4) - (2 * c);
	while (f < 0) f = f + 7;
	f = f%7;
	if (f == 0) return "diumenge";
	else if (f == 1) return "dilluns";
	else if (f == 2) return "dimarts";
	else if (f == 3) return "dimecres";
	else if (f == 4) return "dijous";
	else if (f == 5) return "divendres";
	else return "dissabte";
}

int main() {
	int d, m, a;
	cin >> d >> m >> a;
	cout << dia_de_la_setmana(d, m, a) << endl;
}