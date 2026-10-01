#include <iostream>
#include <vector>
using namespace std;


int solitaris (const vector<int> &v) 
/* Pre: v.size() > 0 */
/* Post: el resultat es el nombre de solitaris a v */
{
  int n = 0;
  bool b = true;	// Primer element sempre diferent anterior
  int i = 1;
  /* Inv: n son el nombre de solitaris en v[0..i-2]
   * 	  1 <= i <= v.size(), i es la posicio següent del vector de l'element que
   * 			      considerem si es solitari o no
   * 	  b indica si v[i-1] es diferent del seu element anterior: v[i-2]
   */
  while (i < v.size()) {
    if (v[i] != v[i-1]) {
      if (b) ++n;	// Si v[i] != v[i-1] i v[i-1] != v[i-2] tenim un solitari mes, v[i-1]
      else b = true;
    }
    else b = false;	// Modifiquem b si es necessari per indicar si v[i] != v[i-1]
    ++i;
  }
  /* A: n val el nombre de solitaris en v[0..v.size()-2]
   * 	b indica si v.size()-1 es difrent de v.size()-2
   */
  if (b) ++n;		// Considerem ultim element sempre diferent següent
  return n;
}
