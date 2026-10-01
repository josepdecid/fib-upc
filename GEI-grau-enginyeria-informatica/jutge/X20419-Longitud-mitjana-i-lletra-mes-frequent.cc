#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int LONG_ALFABET = 'z' - 'a' + 1;

char lletra_mes_frequent(const string& s) {
	vector <int> lmf(LONG_ALFABET, 0);
	int tams = s.size();
	for (int i = 0; i < tams; ++i) {
		++lmf[s[i]-'a'];
	}
	int pos, freq = 0;
	for (int i = 0; i < LONG_ALFABET; ++i) {
		if (lmf[i] > freq) {
			pos = i;
			freq = lmf[i];
		}
	}
	char c = 'a' + pos;
	return c;
}


//Pre: Llegeix un seguit d'n paraules
//Post: Escriu la longitut mitjana i de totes les paraules que tenen una longitut superior a aquesta, la lletra més repetida
int main() {
	cout.setf(ios::fixed);
	cout.precision(2);
	int n;
	double longitut = 0;
	string s;
	cin >> n;
	int aux = n;
	vector<string> v(n); //Guardem la paraula
	vector<int> u(n); //Guardem el tamany de la paraula
	for (int i = 0; i < n; ++i) {
		cin >> s;
		int tams = s.size();
		v[i] = s;
		u[i] = tams;
		longitut += tams;
	}
	longitut /= aux;
	cout << longitut << endl;
	for (int i = 0; i < aux; ++i) {
		if (u[i] >= longitut) {
			cout << v[i] << ": " << lletra_mes_frequent(v[i]) << endl;
		}
	}
}