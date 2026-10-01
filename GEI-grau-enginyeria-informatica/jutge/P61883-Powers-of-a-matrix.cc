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

Matrix power_matrix(const Matrix &M, int n, int m)
{
  Matrix R(2, Row(2));
  if (n == 0) {
    R[0][0] = R[1][1] = 1;
    R[1][0] = R[0][1] = 0;
    return R;
  }
  else {
    R = power_matrix(M, n/2, m);
    Matrix aux(2, Row(2));
    aux = mult_M(R, R, m);
    if (n%2 == 0) return aux;
    else return mult_M(aux, M, m);
  }
}


void write_matrix(const Matrix &M)
{
  cout << M[0][0] << " " << M[0][1] << endl;
  cout << M[1][0] << " " << M[1][1] << endl;
  cout << "----------" << endl;
}

int main()
{
  Matrix M(2, Row(2));
  while (cin >> M[0][0] >> M[0][1] >> M[1][0] >> M[1][1]) {
    int n, m;
    cin >> n >> m;
    Matrix R = power_matrix(M, n, m);
    write_matrix(R);
  }
}
