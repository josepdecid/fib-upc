#include <iostream>
using namespace std;


//Pre: Llegeix 3 enters
//Post: Suma el màxim i el minim
int sum_min_max(int x, int y, int z) {
	int d, g, p;
	if (x <= y && x <= z) {
		p = x;
		if (y <= z) g = z;
		else g = y;
	}
	else if (y <= x && y <= z) {
		p = y;
		if (x <= z) g = z;
		else g = x;
	}
	else {
		p = z;
		if (x <= y) g = y;
		else g = x;
	}
	d = g + p;
	return d;
}

int main() {
	int x, y, z;
	cin >> x >> y >> z;
	cout << sum_min_max(x, y, z) << endl;
}