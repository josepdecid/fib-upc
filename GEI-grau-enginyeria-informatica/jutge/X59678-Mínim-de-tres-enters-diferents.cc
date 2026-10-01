#include <iostream>
using namespace std;

//Precondició: Llegeix tres enters
//Postcondició: En retorna el mínim

int main() {
	int x, y, z;
	cin >> x >> y >> z;
	if (x <= y && x <= z) cout << x << endl;
	else if  (y <= x && y <= z) cout << y << endl;
	else if (z <= x && z <= y) cout << z << endl;
}