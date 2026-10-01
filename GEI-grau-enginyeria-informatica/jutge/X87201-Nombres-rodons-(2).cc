#include <iostream>
using namespace std;


long long canvi_base(int n, int b) {
	long long nb = n%b;
	int mult = 1;
	n = n/b;
	while (n != 0) {
		mult = 10 * mult;
		nb = nb + mult * (n%b);
		n = n/b;
	}
	return nb;
}

bool rodo(int n, int b) {
	int n1 = canvi_base(n, b);
	int count = 0;
	int suma = 0;
	while (n1 != 0) {
		suma = suma + n1%10;
		n1 = n1/10;
		++count;
	}
	if (suma == count) return true;
	return false;
}

int main() {
	int n, b;
	int count = 0;
	bool fi = false;
	while (not fi && cin >> n >> b) {
		if (rodo(n, b)) { 
			if (count == 0) ++count;
			else if (count == 1) ++count;
			else fi = true;
		}
	}
	if (count == 2) cout << "SI" << endl;
	else cout << "NO" << endl;
}