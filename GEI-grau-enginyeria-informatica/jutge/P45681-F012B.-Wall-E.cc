#include <iostream>
#include <vector>
#include <string>
using namespace std;


typedef vector<char> Row;
typedef vector<Row> Matrix;


void read_matrix(Matrix& M) {
	int f = M.size();
	int c = M[0].size();
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			cin >> M[i][j];
		}
	}
}

int move_matrix(Matrix& M, int f, int c, string s) {
	int tam_s = s.size();
	int count = 0;
	for (int k = 0; k < tam_s; ++k) {
		//Actualitzaci贸 posici贸 i suma
		//Nord
		if (s[k] == 'N') {
			while (M[f-1][c] != 'X') {
				if (M[f][c] != '.') {
					count += M[f][c] - '0';
					M[f][c] = '.';
				}
				--f;
			}
		}
		//Sud
		else if (s[k] == 'S') {
			while (M[f+1][c] != 'X') {
				if (M[f][c] != '.') {
					count += M[f][c] - '0';
					M[f][c] = '.';
				}
				++f;
			}
		}
		//Est
		else if (s[k] == 'E') {
			while (M[f][c+1] != 'X') {
				if (M[f][c] != '.') {
					count += M[f][c] - '0';
					M[f][c] = '.';
				}
				++c;
			}
		}
		//Oest
		else if (s[k] == 'O') {
			while (M[f][c-1] != 'X') {
				if (M[f][c] != '.') {
					count += M[f][c] - '0';
					M[f][c] = '.';
				}
				--c;
			}
		}
	}
	//Ultima posicio
	if (M[f][c] != '.') count += M[f][c] - '0';
	return count;
}

void write_matrix(int deixalles, int count) {
	cout << "Cas " << count << ": " << deixalles << endl;
}  

int main() {
	int f, c;
	int count = 0;
	while (cin >> f >> c) {
		++count;
		Matrix M(f, Row(c));
		read_matrix(M);
		string s;
		cin >> f >> c >> s;
		write_matrix(move_matrix(M, f, c, s), count);
	}
}
