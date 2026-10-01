#include <iostream>
#include <vector>
using namespace std;


double producte_escalar(const vector<double>& u, const vector<double>& v) {
	int tam = v.size();
	double escalar = 0;
	for (int i = 0; i < tam; ++i) {
		escalar = escalar + u[i] * v[i];
	}
	return escalar;
}