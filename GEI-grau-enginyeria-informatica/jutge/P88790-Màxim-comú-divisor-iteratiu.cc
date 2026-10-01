#include <iostream>
using namespace std;


int mcd(int a, int b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (b > a) {
		int aux = a;
		a = b;
		b = aux;
	}
	int r;
	while (b != 0) {
		r = a%b;
		a = b;
		b = r;
	}
	return a;
}

//Pre: Llegeix 2 nombres
//Post: N'escriu el mcd utilitzant un algorisme iteratiu
int main() {
	int a, b;
	cin >> a >> b;
	cout << mcd(a, b) << endl;
}