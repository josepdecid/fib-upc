#include <iostream>
#include <vector>
using namespace std;


typedef vector< vector<char> > Matriucar;

typedef vector< vector<bool> > Rep;


//Pre: Rep 2 matrius d'entrada
//Post: Escriu valors a la matriu a i omple la b amb fals
void read_matrix(Matriucar& a, Rep& b) {
	int tam = a.size();
	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
			cin >> a[i][j];
			b[i][j] = false;
		}
	}
}


//Pre: Rep com a valors les dues matrius i una posici贸 inicial
//Post: Escriu el desti dels moviments
void move_matrix(const Matriucar& a, Rep& b, int f, int c) {
	int tam = a.size();
	bool acabat = false;
	while (not acabat) {
		//Explota
		if (a[f][c] == 'X') {
			cout << "kaputt" << endl;
			acabat = true;
		}
		//Es queda sempre dins
		else if (b[f][c] == true) {
			cout << "no escape" << endl;
			acabat = true;
		}		
		//En cas contrari
		else {
			b[f][c] = true;
			//Nord
			if (a[f][c] == 'N') {
				if (f == 0) {
					acabat = true;
					cout << "escape" << endl;
				}
				else --f;
			}
			//Oest
			else if (a[f][c] == 'W') {
				if (c == 0) {
					acabat = true;
					cout << "escape" << endl;
				}
				else --c;
			}
			//Est
			else if (a[f][c] == 'E') {
				if (c == tam-1) {
					acabat = true;
					cout << "escape" << endl;
				}
				else ++c;
			}
			//Sud
			else if (a[f][c] == 'S') {
				if (f == tam-1) {
					acabat = true;
					cout << "escape" << endl;
				}
				else ++f;
			}
		}
	}
}


//Pre: Llegeix m matrius de tamany nxn i una posicio inicial
//Post: Escriu el resultat del despla莽ament per la matriu a
//		   partir de la posicio inicial:
//		   kapput si es destrueix, escape si surt i no escape si es queda per sempre
int main() {
	int m;
	cin >> m;
	while (m != 0) {
		int n, f, c;
		cin >> n >> f >> c;
		Matriucar a(n, vector<char>(n));
		Rep b(n, vector<bool>(n));
		read_matrix(a, b);
		move_matrix(a, b, f, c);
		--m;
	}
}
