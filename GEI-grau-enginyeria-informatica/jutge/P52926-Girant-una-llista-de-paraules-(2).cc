#include <iostream>
#include <string>
using namespace std;


void girar_llista() {
	string x;
	cin >> x;
	if (x != "fi") {
		girar_llista();
		cout << x << endl;
	}
}

//Pre: Llegeix una seqüència de paraules
//Post: Les escriu en ordre invers respecte la entrada
int main() {
	girar_llista();
}