#include <iostream>
#include <vector>
using namespace std;


int comptatge_frontisses(const vector<int> &v) 
/* Pre: cert */
/* Post: el resultat es el nombre d'elements frontissa de v */
{
  int count, suma_left, suma_right;
  count = suma_left = suma_right = 0;
  for (int i = 1; i < v.size(); ++i) {
    suma_right += v[i];
  }
  int i = 0;
  /* Inv: 0 <= i <= v.size()-1, indica la posició del vector que visitem en cada moment
   *      suma_left val la suma de tots els elements de v[0..i-1]
   *      suma_right val la suma de tots els elements de v[i+1..v.size()-1]
   *      count val el nombre de frontisses trobades al vector desde v[0] fins a v[i]
   */
  while (i < v.size()-1) {
    if (v[i] == suma_right - suma_left) ++count;
    ++i;
    suma_right -= v[i];		// Descomptem element actual a la dreta
    suma_left += v[i-1];	// Afegims element anterior a l'esquerra
  }
  /* A:	count indica el nombre de frontisses trobades de v[0..v.size()-2]
   *    suma_left val la suma dels elements de v[0..v.size()-2]
   *	suma_right val 0
   */ 
  if (v[i] == suma_right - suma_left) ++count;
  return count;
}
