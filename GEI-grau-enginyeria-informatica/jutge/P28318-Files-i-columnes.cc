#include <iostream>
using namespace std;


//Pre: LLegeix una matriu
//Post: Escriu la consulta de dades corresponent
int main() {
	//Llegir
	int f, c;
	cin >> f >> c;
	int M[f][c];
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			cin >> 	M[i][j];
		}
	}
	//Consultar
	string s;
	while (cin >> s) {
		cout << s << " ";
		if (s == "fila") {
			int x;
			cin >> x;
			cout << x << ":";
			for (int i = 0; i < c; ++i) {
				cout << " " << M[x-1][i];
			}
		}
		if (s == "columna") {
			int y;
			cin >> y;
			cout << y << ":";
			for (int i = 0; i < f; ++i) {
				cout << " " << M[i][y-1];
			}
		}
		if (s == "element") {
			int x, y;
			cin >> x >> y;
			cout << x << " " << y << ": " << M[x-1][y-1];
		}
		cout << endl;
	}
}