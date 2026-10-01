/* ---------------------------- PilaIOParInt.hh -------------------------------- */

#include "ParInt.hh"
#include <iostream>
#include <stack>
using namespace std;
  
void llegirPilaParInt(stack<ParInt>& p);

void escriurePilaParInt(stack<ParInt> p);

/* ---------------------------- PilaIOParInt.cc -------------------------------- */

#include "PilaIOParInt.hh"

void llegirPilaParInt(stack<ParInt>& p) {
    int a, b;
    while (cin >> a >> b && (a != 0 && b != 0)) {
      ParInt par(a, b);
      p.push(par);
    }
}

void escriurePilaParInt(stack<ParInt> p) {
  int m;
  cin >> m;
  bool found = false;
  int aux;
  while (!p.empty()) {
    ParInt par = p.top();
    par.escriure();
    if (!found && par.primer() == m) {
      found = true;
      aux = par.segon();
    }
    p.pop();
  }
  if (found) cout << aux << endl;
  else cout << "No trobat" << endl;
}

/* ------------------------------- program.cc ---------------------------------- */

#include "PilaIOParInt.hh"

int main() {
  stack<ParInt> p;
  llegirPilaParInt(p);
  escriurePilaParInt(p);
}
