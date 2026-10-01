#include <iostream>
#include <vector>
#include <list>
using namespace std;


void seleccio(const list<double>& l, list<double>& sel) 
/* Pre: l no es buida, sol es buida */
/* Post: sel es el resultat de treure d'l els elements debles en mitjana */
{
  list<double>::const_iterator it1 = l.begin();
  list<double>::iterator it2 = sel.begin();
  sel.insert(it2, *it1); // Mai considerem el primer element feble en mitjana, l'insertem directament
  int nombre = 1;	 // Nombre d'elements visitats per fer la mitjana
  double mitjana = *it1;
  ++it1;
  /* Inv: l.begin() < it1 <= l.end(), it1 apunta a l'element que visitem actualment
   * 	  mitjana dels elements de la llista des de l.begin fins a la pos anterior on apunta it1
   *	  llista sel conté els elements no febles en mitjana de la llista l des de l.begin fins 
   * 	                                               a la posició anterior a la que apunta it1
   * 	  it2 apunta a la ultima posicio de sel
   */
  while (it1 != l.end()) {
    if(*it1 >= mitjana) {  	// Si no es mes petit que la mitjana dels anteriors, no es feble
      sel.insert(it2, *it1);	// I s'ha d'insertar a sel
    }
    mitjana *= nombre;		// Modifiquem la mitjana i el nombre d'elements visitats i avancem per la llista
    ++nombre;
    mitjana += *it1;
    mitjana /= nombre;
    ++it1;
  }
  /* A: it1 == l.end()
   * 	nombre es el nombre d'elements de la llista l
   * 	it2 apunta a la ultima posicio de sel
   * 	sel conte tots els elements no febles en mitjana de la llista l
   */
}
