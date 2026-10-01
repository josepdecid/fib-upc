#include <iostream>
using namespace std;

//Precondició: Llegeix dos enters
//Postcondició: En retorna el mínim

int main() {
	int x, y;
	cin >> x >> y;
	if (x-y >= 0) cout << y << endl;
	else cout << x << endl;
}