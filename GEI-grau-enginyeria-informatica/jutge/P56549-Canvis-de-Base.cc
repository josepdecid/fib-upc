#include <iostream>
using namespace std;


void canvi_base_2(int n) {
	int q;
	q = n/2;
	if (q != 0) canvi_base_2(q);
	cout << n - 2 * q;
}

void canvi_base_8(int n) {
	int q;
	q = n/8;
	if (q != 0) canvi_base_8(q);
	cout << n - 8 *q;
}

void canvi_base_16(int n) {
	int q;
	char k;
	q = n/16;
	if (q != 0) canvi_base_16(q);
	if ((n - 16 * q) >= 10) { //Si està entre 10 o 16 s'expressa entre A i F
		k = 'A' + (n%16) - 10;
		cout << k;
	}
	else cout << n - 16  * q;
}

//Pre: Llegeix un enter
//Post: L'escriu en binari, octal i hexadecimal
int main() {
	int n;
	while (cin >> n) {
		cout << n << " = ";
		canvi_base_2(n);
		cout << ", ";
		canvi_base_8(n);
		cout << ", ";
		canvi_base_16(n);
		cout << endl;
	}
}