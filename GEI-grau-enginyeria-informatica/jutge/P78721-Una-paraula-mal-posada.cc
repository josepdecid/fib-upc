#include <iostream>
#include <string>
using namespace std;


//Pre: Llegeix un seguit de paraules
//Post: Col·loca en la posició correcta la paraula mal ordenada
int main() {
	string s, aux = "a", error;
	bool primer = true;
	bool mal = false;
	while (cin >> s && s != "END") {
		if (s >= aux) {
			if (not primer) cout << aux << endl;
			else primer = false;
			if (mal) {
				if (error >= aux && error <= s) {
					cout << error << endl;
					mal = false;
				}
			}
			aux = s;
		}
		else {
			error = aux;
			aux = s;
			mal = true;
		}
	}
	cout << aux << endl;
	if (mal) cout << error << endl;
}