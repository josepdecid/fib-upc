#include <iostream>
#include <vector>
using namespace std;


int count_digits(int n) {
	int dig = 0;
	while (n != 0) {
		n = n/10;
		++dig;
	}
	return dig;
}

bool es_estrobogramatic(int n) {
	if (n < 10) {
		if (n == 1 or n == 0 or n == 8) return true;
		return false;
	}
	else {
		int digits = count_digits(n);
		vector<int> estrobo(digits);
		for (int i = digits-1; i >= 0; --i) {
			if (n%10 == 2 or n%10 == 3 or n%10 == 4 or n%10 == 7) return false;
			estrobo[i] = n%10;
			n = n/10;
		}
		int i = 0;
		int j = digits-1;
		while (i <= j) {
			if (estrobo[i] == estrobo[j] && (estrobo[i] == 0 or estrobo[i] == 1 or estrobo[i] == 8));
			else if ((estrobo[i] == 6 && estrobo [j] == 9) or (estrobo[i] == 9 && estrobo[j] == 6));
			else return false;
			++i;
			--j;
		}
		return true;
	}
}


int main() {
	int n;
	int count_senar = 0;
	while (cin >> n) {
		if (es_estrobogramatic(n)) cout << n << " si es estrobogramatic" << endl;
		else if (not es_estrobogramatic(n)) cout << n << " no es estrobogramatic" << endl;
		if (es_estrobogramatic(n) && n%2 != 0) ++count_senar;
	}
	cout << endl << "estrobogramatics senars: " << count_senar << endl;
}