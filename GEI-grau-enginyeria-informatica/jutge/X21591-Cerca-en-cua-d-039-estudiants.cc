/* ---------------------------- CuaIOEstudiant.hh -------------------------------- */

#include "Estudiant.hh"
#include <queue>

void LlegirCuaEstudiant(queue<Estudiant> &q);

void EscriureCuaEstudiant(queue<Estudiant> q);

/* ---------------------------- CuaIOEstudiant.cc -------------------------------- */

#include "CuaIOEstudiant.hh"

void LlegirCuaEstudiant(queue<Estudiant> &q) {
  int n;
  cin >> n;
  while (n != 0) {
    Estudiant est;
    est.llegir();
    q.push(est);
    --n;
  }
}

void EscriureCuaEstudiant(queue<Estudiant> q) {
  int ident;
  cin >> ident;
  int aux;
  int found = 0;
  while (!q.empty()) {
    Estudiant est = q.front();
    est.escriure();
    q.pop();
    if (!found) {
      if (est.consultar_DNI() == ident) {
	if (est.te_nota()) {
	  aux = est.consultar_nota();
	  found = 2;
	}
	else found = 1;
      }
    }
  }
  if (found == 0) cout << "No trobat" << endl;
  else if (found == 1) cout << "No te nota" << endl;
  else cout << "La nota es " << aux << endl;
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

#include "CuaIOEstudiant.hh"

int main() {
  queue<Estudiant> q;
  LlegirCuaEstudiant(q);
  EscriureCuaEstudiant(q);
}
