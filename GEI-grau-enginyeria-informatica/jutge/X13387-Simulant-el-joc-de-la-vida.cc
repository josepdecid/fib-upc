#include <iostream>
#include <vector>
using namespace std;


typedef vector<bool> Row;
typedef vector<Row> Matrix;


struct Punt {
    int y;
    int x;
};

void write_matrix(const Matrix& M);

int number_of_B(const Matrix& M, int f, int c, int n) {
    Punt pa, pb, pc;
    pa.y = f;
    pa.x = c;
    pb = pc = pa;
    if (pa.y > 0) {
        --pa.y;
        pb.y = pa.y;
    }
    if (pa.x > 0) --pa.x;
    if (pb.x < n - 1) {
        ++pb.x;
        pc.x = pb.x;
    }
    if (pc.y < n - 1) ++pc.y;
    int found = 0;
    for (int i = pa.y; i <= pc.y; ++i) {
            for (int j = pa.x; j <= pb.x; ++j) {
                if (M[i][j]) {
                    ++found;
                }
            }
        }
    if (M[f][c]) return found - 1;
    else return found;
}


void new_matrix(Matrix& M, int n) {
    bool change = false;
    for (int i = 0; i < n; ++i) {
        if (!change) {
            for (int j = 0; j < n; ++j) {
                if (!M[j][i] && number_of_B(M, j, i, n) == 3) M[j][i] = true;
                else if (M[j][i] && number_of_B(M, j, i, n) >= 2) M[j][i] = true;
                else M[j][i] = false;
            }
            change = true;
        }
        else {
            for (int j = n - 1; j >= 0; --j) {
                if (!M[j][i] && number_of_B(M, j, i, n) == 3) M[j][i] = true;
                else if (M[j][i] && number_of_B(M, j, i, n) >= 2) M[j][i] = true;
                else M[j][i] = false;

            }
            change = false;
        }
    }
    write_matrix(M);
}

bool igual(const Matrix& M1, const Matrix& M2) {
	int tam_m1 = M1.size();
	int tam_m2 = M2.size();
    for (int i = 0; i < tam_m1; ++i) {
        for (int j = 0; j < tam_m2; ++j) {
            if (M1[i][j] != M2[i][j]) return false;
        }
    }
    return true;
}

void write_matrix(const Matrix& M) {
	int tam = M.size();
	for (int i = 0; i < tam; ++i) {
		for (int j = 0; j < tam; ++j) {
            if (M[i][j]) cout << 'B';
            else cout << '.';
        }
        cout << endl;
    }
}

int main(){
    int tam, v;
    cin >> tam >> v;
    Matrix M(tam, Row(tam, false));
    int f, c;
    while (cin >> f >> c) M[f][c] = true;
    write_matrix(M);
    cout << endl;
    Matrix N(tam, Row(tam));
    N = M;
    new_matrix(N, tam);
    cout << endl;
    --v;
    bool first = true;
    bool space = false;
    while (v > 0 && !igual(M, N)) {
        if (!first) cout << endl;
        M = N;
        new_matrix(N, tam);
        first = false;
        --v;
        space = true;
    }
    if (space) cout << endl;
}
