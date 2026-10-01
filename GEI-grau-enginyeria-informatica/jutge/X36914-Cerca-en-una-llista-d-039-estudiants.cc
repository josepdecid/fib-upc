#include "Estudiant.hh"
#include <vector>
#include <list>
using namespace std;

void llegir_llista_est(list<Estudiant>& l){
  list<Estudiant>::iterator it = l.begin();
  Estudiant est;
  est.llegir();
  while (est.consultar_DNI() != 0 && (est.te_nota() && est.consultar_nota() != 0)) {
    l.insert(it, est);
    est.llegir();
  }
}

int cerca_llista_est(const list<Estudiant>& l, int n) {
  int count = 0;
  if (not l.empty()) {
    list<Estudiant>::const_iterator it;
    for (it = l.begin(); it != l.end(); ++it){
      Estudiant aux = *it;
      if (aux.consultar_DNI() == n) ++count;
    } 
  }
  return count;
}

int main() {
  list<Estudiant> llista;
  llegir_llista_est(llista);
  int n;
  cin >> n;
  cout << n << " " << cerca_llista_est(llista, n) << endl;
}
