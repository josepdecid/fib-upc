#include <iostream>
using namespace std;


int nzeros_fact(int x) {
	int nzf = 0;
	for (int i = x; i >= 5; i = i/5) {
		nzf = nzf + (i/5);
	}
	return nzf;
}

//Pre: Llegeix un nombre
//Post: Diu quants zeros té al final del factorial
int main() {
	int x;
	while (cin >> x) {
		cout << nzeros_fact(x) << endl;
	}	
}