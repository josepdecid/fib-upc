#include <iostream>
#include <vector>
#include <string>
using namespace std;


typedef vector<char> Row;
typedef vector<Row> Matrix;


int count(const string& s) {
	int aux = s.size();
	int count = 0;
	for (int i = 0; i < aux; ++i) {
		if (s[i] != '$') ++count;
	}
	return count;	
}


void codify(Matrix& M,const string& s) {
	int f = M.size();
	int c = M[0].size();
	int iterador = 0;
	int k = 0;
	bool augmentar = true;
	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < f; ++j) {
			if (s[k] == '$') ++k;
			if (iterador == j) M[j][i] = s[k];
			else M[j][i] = '.';
		}
		++k;
		if (augmentar && iterador < f - 1) ++iterador;
		else if (augmentar && iterador == f - 1) {
			--iterador;
			augmentar = false;
		}
		else if (not augmentar && iterador > 0) --iterador;
		else if (not augmentar && iterador == 0) {
			++iterador;
			augmentar = true;
		}
	}
}

void write_matrix(Matrix& M, bool& first) {
	if (not first) cout << endl;
	else first = false;
	int f = M.size();
	int c = M[0].size();
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			cout << M[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void write_codified(Matrix& M) {
	int f = M.size();
	int c = M[0].size();
	int count = 0;
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			if (M[i][j] != '.') {
				if (count != 0 && count%5 == 0) cout << " ";
				++count;
				cout << M[i][j];
			}
		}
	}
	cout << endl;
}

//Pre: Llegeix un enter, una string
//Post: La codifica i l'escriu en una matriu d'n x llargada paraula
int main() {
	int f;
	string s;
	bool first = true;
	while (cin >> f) {
		cin >> s;
		int c = count(s);
		Matrix M(f,Row(c));
		codify(M, s);
		write_matrix(M, first);
		write_codified(M);
	}
}