#include <iostream>
using namespace std;


long long base_4(long long n) {
	long long n4 = n%4;
	n = n/4;
	long long mult = 1;
	while (n != 0) {
		mult = mult*10;
		n4 = n4 + mult*(n%4);
		n = n/4;
	}
	return n4;
}

int suma_digits(long long n) {
	long long s = 0;
	while (n != 0) {
		s = s + n%10;
		n = n/10;
	}
	s = 2*s;
	return s;
}

bool es_diabolic(int n) {
	if (n%suma_digits(base_4(n)) == 0) return true;
	else return false;
}

int main() {
	int n, count = 0;
	while (cin >> n && n != -1) {
		if (es_diabolic(n)) ++count;
	}
	int digits = 0;
	for (int i = count; i != 0; i = i/10) {
		++digits;
	}
	if (digits == 6) cout << count << endl;
	else if (digits == 5) cout << '0' << count << endl;
	else if (digits == 4) cout << "00" << count << endl;
	else if (digits == 3) cout << "000" << count << endl;
	else if (digits == 2) cout << "0000" << count << endl;
	else if (digits == 1) cout << "00000" << count << endl;
	else cout << "000000" << endl;
 }