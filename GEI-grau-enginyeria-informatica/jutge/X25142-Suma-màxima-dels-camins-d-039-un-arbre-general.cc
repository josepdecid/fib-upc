static T max_suma_cami_immersive(node_arbreGen *n, bool& valid)
{
	T suma = 0;
	if (n != NULL) {
		valid = true;
		suma = n->info;
		T max = 0;
		for (int i = 0; i < n->seg.size(); ++i) {
			bool rec_valid = false;
			T aux = max_suma_cami_immersive(n->seg[i], rec_valid);
			if (rec_valid && aux > max)
				max = aux;
		}
		if (n->seg.size() > 0) suma += max;
	}
	return suma;
}

T max_suma_cami() const
/* Pre: el parametre implicit no es buit */
/* Post: el resultat es la suma del cami de suma maxima del parametre implicit */
{
	bool valid;
	return max_suma_cami_immersive(this->primer_node, valid);
}
