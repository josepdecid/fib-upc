#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Fila;
typedef vector<Fila> Matriu;

Matriu suma(const Matriu& a, Matriu& b) {
	int tam = a.size();
	Matriu Suma(tam, Fila(tam));
	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
			Suma[i][j] = 	a[i][j] + b[i][j];
		}
	}
	return Suma;
}