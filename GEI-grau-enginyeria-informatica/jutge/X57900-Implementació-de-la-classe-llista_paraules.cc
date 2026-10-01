#include "llista_paraules.hh"


// CREADORES //

llista_paraules::llista_paraules(unsigned int m) {
  midaBloc = m;
  vector<paraula> u(midaBloc);
  v = u;
  posicio = 0;
}


// DESTRUCTORES //

llista_paraules::~llista_paraules() {}



// CONSULTORES //

int cerca_dicot(const vector<paraula> &v, int left, int right, const paraula& par) {
  int i;
  paraula parau = par;
  while (left <= right) {
    i = (left + right)/2;
    if (parau < v[i]) right = i-1; 
    else if (parau > v[i]) left = i + 1; 
    else return i;
  }
  return left;
}

retorn llista_paraules::cerca (const paraula& par) {
  retorn r;
  r.posicio = cerca_dicot(v, 0, posicio - 1, par);
  if (r.posicio < 0 || r.posicio >= midaBloc) r.trobat = false;
  else{
    if (v[r.posicio] == par) r.trobat = true;
    else r.trobat = false;
  }
  return r;
}

long int llista_paraules::frequencia (const string& s) {
  paraula par(s);
  retorn r = cerca(par);
  if (r.trobat) return v[r.posicio].freq();
  else return 0;
}




// MODIFICADORES //

void llista_paraules::insereix(const paraula& par, unsigned int pos) {
  for (unsigned int i = posicio; i > pos; --i) {
    v[i] = v[i - 1];
  }
  v[pos] = par;
  ++posicio;
}

void llista_paraules::redimensiona() {
  midaBloc *= 2;
  vector<paraula> u(midaBloc);
  for (int i = 0; i < posicio; ++i) {
    u[i] = v[i];
  }
  v = u;
}

void llista_paraules::afegeix (const paraula& par) {
  retorn r = cerca(par);
  if (r.trobat) ++v[r.posicio];
  else {
    if (this->posicio == midaBloc) redimensiona();
    insereix(par, r.posicio);
  }
}




// JA IMPLEMENTADES //

void llista_paraules::operator+= (const paraula& par) {

	afegeix (par);
	return;
}

ostream & operator<< (ostream &output, const llista_paraules &l)         
{
	for (unsigned int i = 0 ; i < l.posicio ; i++)
		output << i << "\t" << l.v[i] << endl;
	return output;
};
