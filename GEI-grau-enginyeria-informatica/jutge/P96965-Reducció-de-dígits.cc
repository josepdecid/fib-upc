#include <iostream>
using namespace std;


int suma_digits(int x) {
	int suma = 0;
	while (x > 0) {
		suma = suma + x%10;
		x = x/10;
	}
	return suma;
}

int reduccio_digits(int x) {
	int suma = suma_digits(x);
	if (suma >= 10) return reduccio_digits(suma);
	else return suma;
}

//Pre: Llegeix nombre x
//Post: Obtenim la reducció d'aquest
int main() {
	int x;
	cin >> x;
	cout << reduccio_digits(x) << endl;
}