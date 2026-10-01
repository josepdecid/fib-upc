#include "ListaPalabras.hh"

void ListaPalabras::anadir_palabra(const Palabra &p)
{
/* Pre: el número de palabras en el parámetro implícito es menor que la 
   longitud máxima o p ya está en él; p no es la palabra vacía */
/* Post: si p estaba en el parámetro implícito original, su frecuencia se ha
   incrementado en 1; si no, p pasa a estar en él, con frecuencia 1 */ 
  bool b;
  int j;
  buscar_palabra_posicion(p,b,j);
  if (b) ++paraules[j].freq;
  else {
    paraules[j].par = p;
    paraules[j].freq = 1;
    ++nparaules;
    ++npar_long[p.long_pal() - 1];
  }
  ++suma_frec_long[p.long_pal() - 1];
}

void ListaPalabras::borrar_palabra(const Palabra &p)
{
/* Pre: si p pertence al p.i., tiene frecuencia f */
/* Post:
   si p no pertence al p.i., no cambia nada; 
   si f = 1, p ya no pertenece al p.i.; 
   si f > 1, la frecuencia de p se ha decrementado en 1 */
  bool b;
  int i;
  buscar_palabra_posicion(p,b,i);
  if (b) {
    if (paraules[i].freq > 1) --paraules[i].freq;
    else {
      int allargada = longitud();
      paraules[i] = paraules[allargada - 1];
      --nparaules;
      --npar_long[p.long_pal() - 1];
    }
    --suma_frec_long[p.long_pal() - 1];
  }
}

void ListaPalabras::buscar_palabra_posicion(const Palabra &p, bool &b, int &i) const
{
/* Pre: cierto */
/* Post: b indica si p está en el parámetro implícito;
   si b, entonces i es la posición en la que está p; si no, i es la 
   longitud del parámetro implícito */
  int longi = longitud();
  i = 0;
  b = false;
  while (i < longi && !b) {
    b = (paraules[i].par.iguales(p));
    if (!b) ++i;
  }
}