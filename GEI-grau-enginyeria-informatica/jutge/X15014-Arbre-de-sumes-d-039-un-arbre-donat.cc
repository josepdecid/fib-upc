static void arb_sumes_immersive(node_arbre *n, node_arbre* &m, int &suma)
{
	if (n == NULL) suma = 0;
	else {
		suma = n->info;
		int suma_e, suma_d;
		node_arbre *me = NULL;
		node_arbre *md = NULL;
		arb_sumes_immersive(n->segE, me, suma_e);
		arb_sumes_immersive(n->segD, md, suma_d);
		suma += suma_e + suma_d;
		m = new node_arbre;
		m->info = suma;
		m->segE = me;
		m->segD = md;
	}
}

void arb_sumes(Arbre<int> &asum) const
/* Pre: cert */
/* Post: l'arbre asum ĂŠs l'arbre suma del p.i. */
{
	int suma;
	node_arbre *m = NULL;
	arb_sumes_immersive(this->primer_node, m, suma);
	asum.primer_node = m;
}
