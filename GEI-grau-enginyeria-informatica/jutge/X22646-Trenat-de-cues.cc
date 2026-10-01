void trenat(Cua &c)
/* Pre: p.i. = C1, c = C2 */
/* Post: el p.i. passa a ser el resultat de trenar C1 i C2; c passa a ser buida */
{
	node_cua *pi = this->primer_node;
	node_cua *first_aux = this->primer_node;
	node_cua *cn = c.primer_node;

	if (pi == NULL) this->primer_node = c.primer_node;
	else {
		while (pi != NULL && cn != NULL) {
			node_cua *aux = pi->seguent;
			pi->seguent = cn;
			pi = aux;
			aux = cn->seguent;
			if (pi != NULL) cn->seguent = pi;
			cn = aux;
		}
	}

	this->longitud += c.longitud;
	c.longitud = 0;
	pi = first_aux;
}
