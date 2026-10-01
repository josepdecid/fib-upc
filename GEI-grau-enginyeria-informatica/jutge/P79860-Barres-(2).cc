#include <iostream>
using namespace std;


void pintar_linies(int n) {
    if (n > 1) {
		for (int i = 0; i < n; ++i) cout << '*';
		cout << endl;
		pintar_linies(n - 1);
		pintar_linies(n - 1);
	}
    else {
		cout << '*' << endl;
    }
}

int main() {
	int n;
	cin >> n;
	pintar_linies(n);
}