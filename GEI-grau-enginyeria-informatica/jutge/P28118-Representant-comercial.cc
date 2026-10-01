#include <iostream>
#include <string>
#include <cmath>
using namespace std;


double distancia(double x1, double y1, double x2, double y2) {
	double dist, x, y;
	x = x1 - x2;
	y = y1 - y2;
	dist = sqrt(x*x + y*y);
	return dist;
}

//Pre: Llegeix diferents punts d'un trajecte
//Post: Escriu la distància del recorregut
int main() {
	cout.setf(ios::fixed);
	cout.precision(4);
	string ruta;
	double x, y, aux1, aux2;
	double x1, x2, y1, y2;
	while (cin >> ruta) {
		bool fiseq = false;
		double t = 0;
		cin >> x >> y;
		aux1 = x;
		aux2 = y;
		x1 = x;
		y1 = y;
		while (not fiseq && cin >> x >> y) {
			x2 = x1;
			y2 = y1;
			x1 = x;
			y1 = y;
			t = t + distancia(x1, y1, x2, y2);
			if (x == aux1 && y == aux2) fiseq = true;
		}
		cout << "Trajecte " << ruta << ": " << t << endl;
	}
}