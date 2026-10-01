static int freq_immersive(node_arbreGen *n, const T &x)
{
	int count = 0;
	if (n != NULL) {
		if (n->info == x) ++count;
		for (int i = 0; i < n->seg.size(); ++i) {
			count += freq_immersive(n->seg[i], x);
		}
	}
	return count;
}

int freq(const T& x) const
/* Pre: cert */
/* Post: el resultat indica el nombre d'aparicions de x en el p.i. */
{
	return freq_immersive(this->primer_node, x);
}
