#include "ArbIOparint.hh"


bool search(Arbre<Pari>& a, int n, int& depth, int& m8) {
  if (a.es_buit()) return false;
  else if (a.arrel().first == n) {
    m8 = a.arrel().second;
    return true;
  }
  else {
    Arbre<Pari> a1, a2;
    a.fills(a1, a2);
    ++depth;
    bool s1, s2;
    s1 = search(a1, n, depth, m8);
    s2 = search(a2, n, depth, m8);
    if (!s1 && !s2) --depth;
    return (s1 || s2);
  }
}


bool f_search(Arbre<Pari> a, int n, int& depth, int& m8) {
  return search(a, n, depth, m8);
}


int main() {
  Arbre<Pari> a;
  llegir_arbre_parint(a, 0);
  int n;
  while (cin >> n) {
    int depth = 0;
    int m8;
    if (f_search(a, n, depth, m8)) cout << n << " " << m8 << " " << depth << endl;
    else cout << -1 << endl;
  }
}
