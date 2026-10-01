#include <iostream>
using namespace std;

//Pre: Llegeix dos nombres
//Post: La funció en calcula la diferencia
int dif(int x, int y) {
	int d;
	d = x - y;
	return d;
}

int main() {
	int x, y;
	cin >> x >> y;
	cout << dif(x, y) << endl;
}