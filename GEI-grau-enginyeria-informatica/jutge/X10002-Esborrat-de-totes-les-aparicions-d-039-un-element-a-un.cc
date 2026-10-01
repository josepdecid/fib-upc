void esborrar_tots(const T& x) {
/* Pre: parametre implicit = P */
/* Post: s'han eliminat del parametre implicit totes les aparicions d'x (la
    resta d'elements queda en el mateix ordre que a P); si el punt d'interes de P
    referenciava a una aparicio d'x, passa a referenciar al primer element
    diferent d'x posterior a aquesta (si no hi ha cap element diferent d'x, passa
    a la dreta el tot); en cas contrari, el punt d'interes no canvia */
	node_llista *n = primer_node;
	if (longitud == 1) {
		if (n->info == x) {
			primer_node = NULL;
			ultim_node = NULL;
			act = NULL;
			delete n;
			--longitud;
		}
	}
	else {
		while (n != NULL) {
			if (n->info == x) {
				node_llista *aux = n;
				if (n == primer_node) {
					if (n == act) act = act->seg;
					(n->seg)->ant = NULL;
					primer_node = n->seg;
					n = n->seg;
				}
				else if (n == ultim_node) {
					if (n == act) act = NULL;
					(n->ant)->seg = NULL;
					ultim_node = n->ant;
					n = n->seg;
				}
				else {
					if (n == act) act = act->seg;
					(n->seg)->ant = n->ant;
					(n->ant)->seg = n->seg;
					n = n->seg;
				}
				delete aux;
				--longitud;
			}
			else n = n->seg;
		}
	}
}