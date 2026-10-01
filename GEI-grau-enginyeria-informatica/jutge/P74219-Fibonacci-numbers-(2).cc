#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Row;
typedef vector<Row> Matrix;


Matrix mult_M(const Matrix &M, const Matrix &N, int m)
//Strassen algorithm
{
  int p1, p2, p3, p4, p5, p6, p7;
  p1 = M[0][0]*(N[0][1]-N[1][1]); // A(F-H)
  p2 = (M[0][0]+M[0][1])*N[1][1]; // (A+B)H
  p3 = (M[1][0]+M[1][1])*N[0][0]; // (C+D)E
  p4 = M[1][1]*(N[1][0]-N[0][0]); // D(G-E)
  p5 = (M[0][0]+M[1][1])*(N[0][0]+N[1][1]); // (A+D)(E+H)
  p6 = (M[0][1]-M[1][1])*(N[1][0]+N[1][1]); // (B-D)(G+H)
  p7 = (M[0][0]-M[1][0])*(N[0][0]+N[0][1]); // (A-C)(E+F)
  Matrix R(2, Row(2));
  R[0][0] = (p5 + p4 - p2 + p6)%m;
  R[0][1] = (p1 + p2)%m;
  R[1][0] = (p3 + p4)%m;
  R[1][1] = (p1 + p5 - p3 - p7)%m;
  return R;
}

Matrix fibonacci(const Matrix &M, const int &n, const int &m)
// (0 1)^n-1   (1)   (Fn  )
// (   )     * ( ) = (    )
// (1 1)       (1)   (Fn-1)
{
	if (n <= 1)
		return M;
	else {
		Matrix R = fibonacci(M, n/2, m);
		Matrix aux = mult_M(R, R, m);
		if (n%2 == 0) return aux;
		else return mult_M(aux, M, m);
	}
}


int main()
{
	Matrix M(2, Row(2, 1));
	M[0][0] = 0;
	//Basic Fibonacci Matrix
	int n, m;
	while (cin >> n >> m) {
		if (n <= 1) cout << n << endl;
		else {
			Matrix aux = fibonacci(M, n-1, m); // M^n-1
			cout << (aux[0][0] + aux[0][1])%m << endl;
		}
	}
}
