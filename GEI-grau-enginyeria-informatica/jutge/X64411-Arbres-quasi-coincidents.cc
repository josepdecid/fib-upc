#include "Arbre.hh"


bool search_differences(Arbre<int>& a, Arbre<int>& b, bool& odif) 
{
  bool aux;
  if ((a.es_buit() && !b.es_buit()) || (b.es_buit() && !a.es_buit())) {
    if (odif) aux = false;
    else {
      if (!b.es_buit()) {
        Arbre<int> b_aux(b), b1, b2;
        b_aux.fills(b1, b2);
        if (b1.es_buit() && b2.es_buit()) aux = true;
        else aux = false;
      }
      else if (!a.es_buit()) {
        Arbre<int> a_aux(a), a1, a2;
	a_aux.fills(a1, a2);
	if (a1.es_buit() && a2.es_buit()) aux = true;
	else aux = false;
      }
      odif = true;
    }
  }
  else if (a.es_buit() && b.es_buit()) aux = true;
  else {
    Arbre<int> a1, a2, b1, b2;
    a.fills(a1, a2);
    b.fills(b1, b2);
    aux = search_differences(a1, b1, odif);
    if (aux) aux = search_differences(a2, b2, odif);
  }
  return aux;
}


bool quasi_coincidents (Arbre<int> &a, Arbre<int> &b)
/* Pre: a=A, b=B */
/* Post: el resultat indica si A i B son quasi coincidents */
{
  bool odif = false;
  return search_differences(a, b, odif);
}
