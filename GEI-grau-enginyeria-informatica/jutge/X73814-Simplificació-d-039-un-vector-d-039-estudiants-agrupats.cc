#include "Estudiant.hh"

#include <iostream>
#include <vector>
using namespace std;


void llegir(vector<Estudiant>& v){
  int vsize;
  cin >> vsize;
  v = vector<Estudiant> (vsize);
  for(int i = 0; i < vsize; ++i){
    int DNI;
    double mark;
    cin >> DNI;
    Estudiant al(DNI);
    v[i] = al;
    cin >> mark;
    if (0 <= mark && mark <= 10) v[i].afegir_nota(mark);
  }
}

int new_size(const vector<Estudiant>& v) {
  int tam = v.size();
  int new_tam = 0;
  int dni = -1;
  for (int i = 0; i < tam; ++i) {
    if (v[i].consultar_DNI() != dni) {
      ++new_tam;
      dni = v[i].consultar_DNI();
    }
  }
  return new_tam;
}


void simplifica(const vector<Estudiant>& v, vector<Estudiant>& u) {
  int it = -1;
  int dni = -1;
  int tam = v.size();
  for (int i = 0; i < tam; ++i) {
    int DNI = v[i].consultar_DNI();
    if(DNI != dni) {
      dni = DNI;
      ++it;
      Estudiant al(DNI);
      u[it] = al;
      if (v[i].te_nota()) u[it].afegir_nota(v[i].consultar_nota());
    }
    else {
      if (v[i].te_nota()) {
	if (u[it].te_nota()) {
	  double mark = v[i].consultar_nota();
	  if (u[it].consultar_nota() < mark) u[it].modificar_nota(mark);
	}
	else u[it].afegir_nota(v[i].consultar_nota());
      }
    }
  }
}

void escriu(const vector<Estudiant>& u) {
  int tam = u.size();
  for (int i = 0; i < tam; ++i) u[i].escriure();
}


int main () {
  vector<Estudiant> v;
  llegir(v);
  vector<Estudiant> u(new_size(v));
  simplifica(v, u);
  escriu(u);
}
