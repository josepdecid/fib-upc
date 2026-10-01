----------------------------------TRADITIONAL WAY-----------------------------------------

void concat(Cua &c)
/* Pre: c=C */
/* Post: el p.i. passa a ser la concatenació de C al paràmetre implícit, c és buida. */
{
  while (!c.es_buida()) {
    demanar_torn(c.primer());
    c.avancar();
  }
}

----------------------------------POINTERS-------------------------------------------------

void concat(Cua &c)
/* Pre: c=C */
/* Post: el p.i. passa a ser la concatenació de C al paràmetre implícit, c és buida. */
{
  if (c.longitud != 0) {
    if (longitud == 0) { //El paràmentre implícit està buit;
      primer_node = c.primer_node;
      ultim_node = c.ultim_node;
      longitud = c.longitud;
    }
    else if (longitud != 0 && c.longitud != 0) { //Cap de les dues cues està buida. */
      ultim_node->seguent = c.primer_node;
      ultim_node = c.ultim_node;
      longitud += c.longitud;
    }
      c.longitud = 0;
      c.primer_node = NULL;
      c.ultim_node = NULL;
  }
  //En qualssevol altre cas no cal realitzar cap operació.
}


----------------------------------TEST PROGRAM---------------------------------------------

#include <iostream>
#include "Cua.hh"

int main()
{
  Cua<int> c;
  int n;
  while (cin >> n && n != 0) { //Utilitzem 0 com a sentinella
    c.demanar_torn(n);
  }
  Cua<int> c2;
  while (cin >> n && n != 0) { //Utilitzem 0 com a sentinella
    c2.demanar_torn(n);
  }
  c.concat(c2);
  while (!c.es_buida()) {
    cout << c.primer() << endl;
    c.avancar();
  }
}

-------------------------------------------------------------------------------------------
