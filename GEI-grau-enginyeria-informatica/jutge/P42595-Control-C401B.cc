#include <iostream>
#include <vector>
using namespace std;


typedef vector< vector<int> > Matriu;

void read_matrix(Matriu& mat) {
	int f = mat.size();
	int c = mat[0].size();
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			cin >> mat[i][j];
		}
	}
}

void min_max(Matriu& mat, int& minim, int& maxim) {
	int f = mat.size();
	int c = mat[0].size();
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			if (mat[i][j] > maxim) maxim = mat[i][j];
			if (mat[i][j] < minim) minim = mat[i][j];
		}
	}
}

int main() {
	int f, c;
	int dif_max = 0;
	int count = 0;
	int primer = 1;
	while (cin >> f >> c) {
		Matriu mat(f, vector<int>(c));
		read_matrix(mat);
		++count;
		int min = mat[0][0];
		int max = mat[0][0];
		min_max(mat, min, max);
		int dif = max - min;
		if (dif > dif_max) {
			dif_max = dif;
			primer = count;
		}
	}
	cout << "la diferencia maxima es " << dif_max << endl;
	cout << "la primera matriu amb aquesta diferencia es la " << primer << endl;
}