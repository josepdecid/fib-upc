#include <iostream>
using namespace std;


int nombre_digits(int n) {
	if (n < 10) return 1;
	else return 1 + nombre_digits(n/10);
	
}

//Pre: Llegeix un enter
//Post: Obtenim el nombre de dígits
int main() {
	int n;
	cin >> n;
	cout << nombre_digits(n) << endl;
}