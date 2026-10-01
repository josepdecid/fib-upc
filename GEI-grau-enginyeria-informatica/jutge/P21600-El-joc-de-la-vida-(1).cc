#include <iostream>
#include <vector>
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

void wrote_matrix(Matrix& M) {
	int f = M.size();
	int c = M[0].size();
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			cout << M[i][j];
		}
		cout << endl;
	}
}

int count_pos(const Matrix& M, int i, int j) {
	int f = M.size();
	int c = M[0].size();
	int add_i = i + 1;
	int add_j = j + 1;
	int sub_i = i - 1;
	int sub_j = j - 1;
	bool exists_add_i = add_i < f;
	bool exists_add_j = add_j < c;
	bool exists_sub_i = sub_i >= 0;
	bool exists_sub_j = sub_j >= 0;
	int count = 0;
	if (exists_sub_i && M[sub_i][j] == 'B') ++count; //Nord
	if (exists_sub_j && M[i][sub_j] == 'B') ++count; //Oest
	if (exists_add_i && M[add_i][j] == 'B') ++count; //Sud
	if (exists_add_j && M[i][add_j] == 'B') ++count; //Est
	if (exists_sub_i && exists_sub_j && M[sub_i][sub_j] == 'B') ++count; //Nord-oest
	if (exists_sub_i && exists_add_j && M[sub_i][add_j] == 'B') ++count; //Nord-est 
	if (exists_add_i && exists_add_j && M[add_i][add_j] == 'B') ++count; //Sud-est
	if (exists_add_i && exists_sub_j && M[add_i][sub_j] == 'B') ++count; //Sud-oest
	return count;
}

Matrix modify_matrix(const Matrix& M) {
	int f = M.size();
	int c = M[0].size();
	Matrix next_state(f, Row(c));
	next_state = M;
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			int aux = count_pos(M, i, j);
			if (M[i][j] == '.' && aux == 3) next_state[i][j] = 'B';
			else if (M[i][j] == 'B' && aux != 2 && aux != 3) next_state[i][j] = '.';
		}
	}
	return next_state;
}

int main() {
	int f, c;
	bool primer = true;
	while (cin >> f >> c && (f != 0 && c != 0)) {
		if (not primer) cout << endl;
		else primer = false;
		Matrix M(f, Row(c));
		read_matrix(M);
		Matrix Result(f, Row(c));
		Result = modify_matrix(M);
		wrote_matrix(Result);
	}
}