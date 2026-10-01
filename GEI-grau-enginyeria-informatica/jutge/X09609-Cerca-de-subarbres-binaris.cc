static node_arbre* sub_arrel_immersive(node_arbre *n, const T &x, int &depth)
{
	node_arbre* p = NULL;
	if (n != NULL) {
		if (n->info == x) {
			p = copia_node_arbre(n);
		}
		else {
			int depth1, depth2;
			depth1 = depth2 = depth + 1;
			node_arbre *p_aux = NULL;
			p = sub_arrel_immersive(n->segE, x, depth1);
			p_aux = sub_arrel_immersive(n->segD, x, depth2);
			if (p == NULL) {
				p = p_aux;
				depth += depth2;
			}
			else if (p != NULL && p_aux != NULL) {
				if (depth1 > depth2) {
					p = p_aux;
					depth += depth2;
				}
			}
			else depth += depth1;
		}
	}
	return p;
}

void sub_arrel(Arbre& asub, const T& x)
/* Pre: p.i. = A, asub es buit */
/* Post: si A conte x, asub es el subarbre d'A resultat de la cerca;
   si A no conte x, asub es buit */
{
	int depth = 0;
	asub.primer_node = sub_arrel_immersive(this->primer_node, x, depth);

}
