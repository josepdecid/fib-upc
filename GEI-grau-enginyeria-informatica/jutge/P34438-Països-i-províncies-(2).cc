#include <iostream>
#include <vector>
using namespace std;


struct Provincia {
	string nom;
	string capital;
	int habitants;
	int area;
	double pib;
};

struct Pais {
	string nom;
	string capital;
	vector<Provincia> provs;
};

typedef vector<Pais> Paisos;

int habitants(const Paisos& p, double x) {
	int tam_p = p.size();
	int suma_hab = 0;
	for (int i = 0; i < tam_p; ++i) {
		int sum_provs_less_x = 0;
		int tam_provs = p[i].provs.size();
		for (int j = 0; j < tam_provs; ++j) {
			if (p[i].provs[j].pib <= x) ++sum_provs_less_x;
			if (sum_provs_less_x == 2) j = tam_provs;
		}
		if (sum_provs_less_x >= 2) {
			for (int j = 0; j < tam_provs; ++j) {
				suma_hab += p[i].provs[j].habitants;
			}
		}
	}
	return suma_hab;
}