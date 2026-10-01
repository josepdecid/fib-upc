#include "Estudiant.hh"

#include <iostream>
#include <vector>
using namespace std;


void modify(vector<bool>& v, int 	S) {
  int n;
  for (int i = 0; i < S; ++i) {
    cin >> n;
    v[n-1] = true;
  }
}

void operate(vector<Estudiant>& v, const vector<bool>& assig, int s, int N) {
  int tam_v = v.size();
  for (int i = 0; i < tam_v; ++i) {
    int dni;
    cin >> dni;
    Estudiant al(dni);
    v[i] = al;
    double mark = 0;
    for (int j = 0; j < N; ++j) {
      double nota;
      cin >> nota;
      if (assig[j]) {
	mark += nota;
      }
    }
    mark /= s;
    v[i].afegir_nota(mark);
  }
}

void escriu(const vector<Estudiant>& u) {
  int tam = u.size();
  for (int i = 0; i < tam; ++i) u[i].escriure();
}



int main() {
  int M, N, S;
  cin >> M >> N >> S;
  vector<bool> assig(N, false);
  modify(assig, S);
  vector<Estudiant> v(M);
  operate(v,assig,S,N);
  escriu(v);
}