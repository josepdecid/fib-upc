#include <iostream>
#include <cmath>
using namespace std;

struct Punt {
	double x, y;
};

void llegeix_punt(Punt& n) {
	cin >> n.x >> n.y;
}

double distancia(const Punt& a, const Punt& b) {
	double de;
	de = (b.x - a.x)*(b.x - a.x) + (b.y  - a.y)*(b.y - a.y);
	de = sqrt(de);
	return de;
}

int main () {
	Punt a, b;
	llegeix_punt(a);
	llegeix_punt(b);
	cout << distancia(a, b) << endl;
}