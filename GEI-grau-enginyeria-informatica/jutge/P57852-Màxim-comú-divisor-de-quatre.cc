#include <iostream>
using namespace std;


int mcd4(int a, int b, int c, int d) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (c < 0) a = -c;
	if (d < 0) b = -d;
	if (b > a) {
		int aux = a;
		a = b;
		b = aux;
	}
	if (d > c) {
		int aux1 = c;
		c = d;
		d = aux1;
	}
	int r1;
	while (b != 0) {
		r1 = a%b;
		a = b;
		b = r1;
	}
	int r2;
	while (d != 0) {
		r2 = c%d;
		c = d;
		d = r2;
	}
	if (c > a) {
		int aux1 = a;
		a = c;
		c = aux1;
	}
	int r;
	while (c != 0) {
		r = a%c;
		a = c;
		c = r;
	}
	return a;
}

//Pre: Llegeix 4 nombres
//Post: Calcula l'mcd
int main() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	cout << mcd4(a, b, c, d) << endl;
}