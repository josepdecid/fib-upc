#include "ArbIOest.hh"


bool search(Arbre<Estudiant>& a, int ident, int& depth, int& mark) {
  if (a.es_buit()) return false;
  else if (a.arrel().consultar_DNI() == ident) {
    if (a.arrel().te_nota()) mark = a.arrel().consultar_nota();
    else mark = -1;
    return true;
  }
  else {
    Arbre<Estudiant> a1, a2;
    a.fills(a1, a2);
    ++depth;
    bool s = search(a1, ident, depth, mark);
    if (s) return true;
    else s = search(a2, ident, depth, mark);
    if (!s) --depth;
    return s;
  }
}


bool f_search(Arbre<Estudiant> a, int ident, int& depth, int& mark) {
  return search(a, ident, depth, mark);
}


int main() {
  Arbre<Estudiant> a;
  llegir_arbre_est(a, 0);
  int ident;
  while (cin >> ident) {
    int depth = 0;
    int mark;
    if (f_search(a, ident, depth, mark)) {
      cout << "L'estudiant " << ident << " té profunditat " << depth;
      if (mark == -1) cout << ", però no té nota" << endl;
      else cout << " i la seva nota és " << mark << endl;
    }
    else cout << "L'estudiant " << ident << " no hi és" << endl;
  }
}
