#include <iostream>
using namespace std;


int engreixa(int x) {
	int count = 0;
	for (int i = x; i != 0; i = i/10) ++count;
	int ix; //inversa x
	ix = x%10;
	x = x/10;
	for (int i = x; i != 0; i = i/10) ix = ix*10 + i%10;
	x = ix%10;
	ix = ix/10;
	int aux = x;
	--count;
	while (ix != 0 or count != 0) {
		if (ix%10 > aux) {
			x = x*10 + ix%10;
			aux = ix%10;
		}
		else x = x*10 + aux;
		ix = ix/10;
		--count;
	}
	return x;
}
	
//Pre: Llegeix un nombre
//Post: Engreixa el nombre
//Engreixar és canviar la següent xifra per l'actual 
//si la següent és més petita
int main() {
	int x;
	cin >> x;
	cout << engreixa(x) << endl;
}