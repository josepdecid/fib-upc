#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct par {
  int a, b;
};

void llegir_llista_par(list<par>& l, par marca){
  list<par>::iterator it = l.begin();
  par p;
  cin >> p.a >> p.b;
  while (p.a != marca.a && p.b != marca.b) {
    l.insert(it, p);
    cin >> p.a >> p.b;
  }
}

par cerca_llista_par(const list<par>& l, int n) {
  par result;
  result.a = result.b = 0;
  if (not l.empty()) {
    list<par>::const_iterator it;
    for (it = l.begin(); it != l.end(); ++it){
      par aux = *it;
      if (aux.a == n) {
	++result.a;
	result.b += aux.b;
      }
    } 
  }
  return result;
}

int main() {
  list<par> llista;
  par marca;
  marca.a = marca.b = 0;
  llegir_llista_par(llista, marca);
  int n;
  cin >> n;
  par result = cerca_llista_par(llista, n);
  cout << n << " " << result.a << " " << result.b << endl;
}
