#include <iostream>
#include <vector>
using namespace std;


typedef vector< vector<int> > Matriu;


int suma_diagonals(const Matriu& mat) {
	int tam = mat.size();
	int suma = 0;
	int i = 0, j = 0;
	while (i < tam && j < tam) {
		suma += mat[i][j];
		++i;
		++j;
	}
	i = tam-1;
	j = 0;
	while (i >= 0 && j < tam) {
		suma += mat[i][j];
		--i;
		++j;
	}
	if (tam%2 != 0) suma -= mat[tam/2][tam/2];
	return suma;
}

void read_matrix(Matriu& mat){
	int tam = mat.size();
	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
			cin >> mat[i][j];
		}
	}
}

int main() {
	int tam;
	while (cin >> tam) {
		Matriu mat(tam, vector<int>(tam));
		read_matrix(mat);
		cout << suma_diagonals(mat) << endl;
	}
}
