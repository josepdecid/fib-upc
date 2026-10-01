#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Fila;
typedef vector<Fila> Matriu;

bool es_simetrica(const Matriu& m) {
	int tam_m = m.size();
	for (int i = 0; i < tam_m; ++i) {
		for (int j = 0; j < tam_m; ++j) {
			if (m[i][j] != m[j][i]) return false;
		}
	}
	return true;
}