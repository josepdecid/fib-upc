#include <iostream>
#include <vector>
#include <string>
using namespace std;


string concatenar(string a, string b) {
	int tam_a = a.size();
	int tam_b = b.size();
	string c(tam_a + tam_b, ' ');
	for (int i = 0; i < tam_a; ++i) c[i] = a[i];
	for (int i = 0; i < tam_b; ++i) c[i+tam_a] = b[i];
	return c;
}

int pos(string s, const vector<string>& v) {
	for (int i = 0; i < 16; ++i) {
		if (v[i] == s) return i;
	}
	return -1;
}


int main() {
	vector<string> v(16);
	v[0] = "a";
	v[1] = "b";
	for (int i = 2; i < 16; ++i) v[i] = concatenar(v[i-2], v[i-1]);
	string s;
	while (cin >> s) {
		int aux = pos(s, v);
		if (aux < 0) cout << s << " no es de Fibonacci" << endl;
		else cout << s << " es la paraula numero " << aux + 1 << endl;
	}
}
