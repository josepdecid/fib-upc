#include <iostream>
using namespace std;


int mcd(int a, int b) { //m.c.d recursiu
	if (b != 0) return mcd(b, a%b); 
	else return a;		
	}

//Pre: Llegeix dos naturals
//Post:	Retorna l'mcd
int main() {
	int a, b;
	cin >> a >> b;
	cout << mcd(a, b) << endl;
}