#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int LONG_ALFABET = 'z' - 'a' + 1;

void escriu_fals(const vector<bool>& v) {
	for (int i = 0; i < LONG_ALFABET; ++i) {
		if (v[i] == false) cout << char('a' + i) << endl;
	}
}


//Pre: Llegeix un seguit d'n paraules
//Post: Escriu la paraula més llarga i les lletres de l'alfabet que no apareixen a la seqüència
int main() {
	vector<bool> v(LONG_ALFABET, false);
	int n, llarg = 0;
	cin >> n;
	string s, pllarg;
	while (n != 0) {
		cin >> s;
		int tams = s.size();
		if (tams > llarg) {
			pllarg = s;
			llarg = tams;
		}
		for (int i = 0; i < tams; ++i) {
			v[int(s[i]-'a')] = true;
		}
		--n;
	}
	cout << pllarg << endl;
	escriu_fals(v);
}