#include <iostream>
using namespace std;


//Pre: Llegeix diversos naturals >= 2
//Post: Escriu un octàgon de mida n
int main() {
	int n;
	while (cin >> n) {
		int ce = n-1, cx = n; //Comparador espais ce i comparador x cx
		for (int s = n-1; s != 0; --s) { //Files superiors
			for (int e = ce; e != 0; --e) {
				cout << ' ';
			}
			for (int x = cx; x != 0; --x) {
				cout << 'X';
			}
			cout << endl;
			cx = cx + 2;
			--ce;
		}
		for (int s = n; s != 0; --s) { //Files centrals
			for (int e = cx; e != 0; --e) {
				cout << 'X';
			}
			cout << endl;
		}
		cx = cx - 2;
		ce = 1;
		for (int s = n-1; s != 0; --s) { //Files inferiors
			for (int e = ce; e != 0; --e) {
				cout << ' ';
			}
			++ce;
			for (int x = cx; x != 0; --x) {
				cout << 'X';
			}
			cx = cx -2;
			cout << endl;
		}
		cout << endl;
		}
}