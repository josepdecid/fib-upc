#include <iostream>
#include <vector>
using namespace std;


typedef vector<int> Columna;
typedef vector<Columna> Matriu;

bool ZigaZaga(const Matriu& M, int f, int c) {
	int comp = M[0][0];
	bool primer = true;
	for (int j  = 0; j < c; ++j) {
				if (j%2 == 0) { //Baixar
					for (int i =0; i < f; ++i) {
						if (not primer) {
							if (M[i][j] <= comp) return false;
							else comp = M[i][j];
						}
						primer = false;
					}
				}
				else { //Pujar
					for (int i = f-1; i >= 0; --i) {
						if (M[i][j] <= comp) return false;
						else comp = M[i][j];
					}
				}
	}
	return true;
}

int main() {
	int f, c;
	int count = 0;
	while (cin >> f >> c) {
		++count;
		Matriu M(f, Columna(c));
		for (int i = 0; i < f; ++i) {
			for (int j = 0; j < c; ++j) cin >> M[i][j];
		}
		if (ZigaZaga(M, f, c)) cout << "matriu " << count << ": si" << endl;
		else cout << "matriu " << count << ": no" << endl;
	}
}