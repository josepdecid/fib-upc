#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Columna;
typedef vector<Columna> Matriu;

Matriu producte(const Matriu& a, Matriu& b) {
	int tam = a.size();
	Matriu Producte(tam, Columna(tam));
	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
			int aux = 0;
			for (int k = 0; k < tam; ++k) {
				aux += a[i][k] * b[k][j];
			}
			Producte[i][j] = aux;
		}
	}
	return Producte;
}

int main() {
	int f, c;
	cin >> f >> c;
	Matriu a(f, Columna(c));
	Matriu b(f, Columna(c));
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			cin >> b[i][j];
		}
	}
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			cout << producte(a, b)[i][j] << " ";
		}
		cout << endl;
	}
}