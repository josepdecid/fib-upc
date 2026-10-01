#include <iostream>
using namespace std;


int intercalacio(int x, int y) {
	int i = 0;
	int mult = 1;
	while (x != 0 or y != 0) {
		i = mult*((y%10) + (x%10)*10) + i;
		mult = mult *100;
		x = x/10;
		y = y/10;
	}
	return i;	
}

//Pre: Llegeix 2 naturals
//Post: Els escriu intercaladament
int main() {
	int x, y;
	while (cin >> x) {
		cin >> y;
		cout << intercalacio(x, y) << endl;
	}
}