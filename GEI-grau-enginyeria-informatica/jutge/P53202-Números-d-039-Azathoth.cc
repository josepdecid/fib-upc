#include <iostream>
#include <vector>
using namespace std;


int canvi_base_2(int n) {
    int b2 = 0;
    int mult = 1;
    while (n != 0) {
		b2 = mult*(n%2) + b2;
		n = n/2;
		mult = mult * 10;
	}
	return b2;     
}

void escriu_binari(int n) {
	int digits = 1;
	for (int i = n/50; i != 0; i = i/50) {
		++digits;
	}
	vector<int> azathoth(digits);
	for (int i = digits-1; i >= 0; --i) {
		azathoth[i] = n%50;
		n = n/50;
	}
	for (int j = 0; j <= digits-1; ++j) {
		int conv_bin = azathoth[j];
		int bin = canvi_base_2(conv_bin);
		cout << '.' << bin;
	}
}

//Pre: Llegeix un nombre natural
//Post: Retorna la seqüència en binari a partir de la base 50
int main() {
	int n;
	while (cin >> n) {
		cout << n << " = ";
		escriu_binari(n);
		cout << '.';
		cout << endl;
	}
}