#include <iostream>
#include <vector>
#include <string>
using namespace std;


struct Paraula {
	string contingut;	//La paraula
	int consonants; 	//Nombre d'aparicions de consonants
};


typedef vector< vector<Paraula> > MatParaules;


void read_matrix(MatParaules& M) {
	int f = M.size();
	int c = M[0].size();
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			cin >> M[i][j].contingut;
			int tam = M[i][j].contingut.size();
			int consonants = 0;
			for (int k = 0; k < tam; ++k) {
				if (M[i][j].contingut[k] != 'A') {
					if (M[i][j].contingut[k] != 'E') {
						if (M[i][j].contingut[k] != 'I') {
							if (M[i][j].contingut[k] != 'O') {
								if (M[i][j].contingut[k] != 'U') ++consonants;
							}
						}
					}
				}
			}
			M[i][j].consonants = consonants;
		}
	}
}

void search_cons(const MatParaules& M, int k) {
	int f = M.size();
	int c = M[0].size();
	int x, y;
	bool trobat = false;
	for (int i = 0; i <= f-k && not trobat; ++i) {
		for (int j = 0; j <= c-k && not trobat; ++j) {
			int comp = 0;
			bool error = false;
			for (int aux = 0; aux < k && not error; ++aux) {
				if (M[i+aux][j+aux].consonants > comp) comp = M[i+aux][j+aux].consonants;
				else error = true;
			}
			if (not error) {
				trobat = true;
				x = i;
				y = j;
			}
		}
	}
	if (not trobat) cout << "-1 -1" << endl;
	else {
		cout << x << " " << y << " " << M[x][y].contingut << endl;
	}
}

int main() {
	int f, c, k;
	cin >> f >> c >> k;
	MatParaules M(f, vector<Paraula>(c));
	read_matrix(M);
	search_cons(M, k);
}
