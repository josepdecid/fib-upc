#include <iostream>
using namespace std;


int exponent(int n) {
	int exp = 1;
	int suma = 0;
	int n1, sumap;
	int aux = n;
	int pot = exp;
	while (suma < aux) {
		exp = pot;
		n1 = n%10;
		sumap = n1;
		n = n/10;
		--exp;
		for (int i = exp; i != 0; --i) {
			sumap = sumap * n1;
		}
		suma = suma + sumap;
		if (n == 0) {
			++pot;
			n = aux;
			suma = 0;
		}
	}
	--pot;
	return pot;
}

bool es_narcicista(int n) {
	if (n >= 10) {
		int k = exponent(n);
		int n1, n2;
		int aux = n;
		int suma = 0;
		while (n != 0) {
			int i = k;
			n1 = n%10;
			n2 = n1;
			n = n/10;
			--i;
			while (i != 0) {
				n1 = n1 * n2;
				--i;
			}
			suma = suma + n1;
		}
		if (suma == aux) return true;
		return false;
	}
	else return true;
}


int main() {
	int n;
	bool narc = true;
	while (cin >> n && narc) {
		if (not es_narcicista(n)) narc = false;
	}
	if (narc) cout << "SI" << endl;
	else cout << "NO" << endl;
}