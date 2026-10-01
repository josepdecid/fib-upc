#include <iostream>
using namespace std;

//Precondició: Hem d'entrar un caràcter alfanumèric
//Postcondició: Escriu el tipus de caràcter

int main() {
	char x;
	cin >> x;
	if (x >= 65 && x <= 90) cout << "Lletra majuscula" << endl;
	else if (x >= 97 && x <= 122) cout << "Lletra minuscula" << endl;
	else cout << "Numero" << endl;
}