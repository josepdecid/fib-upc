#include <iostream>
using namespace std;


int base_3(int x) {
	int aux;
	int err;
	err = x%3 +1;
	aux = err;
	x = x/3;
	while (x != 0) {
		err = x%3 + 1;
		aux = 10*aux + err;
		x = x/3;
	}
	return aux;
}

//Pre: Llegeix un enter en decimal
//Post: El codifica en base 3 (0 -> '-', 1 -> '+', 2 -> '*')
int main() {
	int x;
	while (cin >> x) {
		if (x < 0) {
			x = -1*x;
			cout << ':';
		}
		x = base_3(x);
		while (x != 0) {
			if (x%10 == 1) cout << '-';
			else if (x%10 == 2) cout << '+';
			else if (x%10 == 3) cout << '*';
			x = x/10;
		}
		cout << endl;
	}
}