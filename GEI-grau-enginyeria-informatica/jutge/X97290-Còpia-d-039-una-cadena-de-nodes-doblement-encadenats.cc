node_llista* copia_node_llista_it (node_llista* m, node_llista* oact, node_llista* &u, node_llista* &a)
/* Pre: cert */
/* Post: si m és NULL, el resultat, u i a són NULL; en cas
       contrari, el resultat apunta al primer node d'una cadena de
       nodes que són còpia de la cadena que té el node apuntat per m
       com a primer, u apunta a l'últim node, a és o bé NULL si oact
       no apunta a cap node de la cadena que comença amb m o bé apunta
       al node còpia del node apuntat per oact */
{
  if (m == NULL) {
    u = a = NULL;
    return m;
  }
  else {
    a = NULL;
    node_llista* primer_node_copia = NULL;
    bool first = true;
    node_llista* aux = NULL;
    while (m != NULL) {
      node_llista* nou_node = new node_llista;
      nou_node->info = m->info;
      if (aux != NULL) aux->seg = nou_node;
      nou_node->ant = aux;
      if (first) {
	first = false;
	primer_node_copia = nou_node;
      }
      if (oact == m) {
	a = nou_node;
      }
      aux = nou_node;
      m = m->seg;
    }
    u = aux;
    return primer_node_copia;
  }
}

void borrar_llista(node_llista* n) {
  if (n != NULL) {
    borrar_llista(n->seg);
    delete n;
    n = NULL;
  }
}

Llista& operator=(const Llista& original) 
/* Pre: cert */
/* Post: El p.i. passa a ser una còpia d'original i qualsevol
   contingut anterior del p.i. ha estat esborrat (excepte si el
   p.i. i original ja eren el mateix objecte) */
{
   if (this != &original) {
      longitud = original.longitud;
      borrar_llista(this->primer_node);
      primer_node = copia_node_llista_it(original.primer_node, original.act, ultim_node, act);
   }
   return *this;
}
