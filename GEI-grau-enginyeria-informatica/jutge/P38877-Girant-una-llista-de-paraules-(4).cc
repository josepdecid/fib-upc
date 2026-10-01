#include <iostream>
using namespace std;


void girar_llista(int& n) {
	string x;
	if (cin >> x) {
		girar_llista(n);
		if (n != 0) {
			cout << x << endl;
			--n;
		}
	}
}

int main() {
	int n;
	cin >> n;
	girar_llista(n);
}