//Retorna true si es any de traspàs
bool es_any_de_traspas(int any) {
	if (any%4 == 0 && any%100 != 0) return true;
	else if (any%100 == 0 && (any/100)%4 == 0) return true;
	else return false;
}