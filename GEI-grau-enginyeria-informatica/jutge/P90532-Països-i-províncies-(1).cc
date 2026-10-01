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

double pib(const Paisos& p, char c, double d) {
	int tam_p = p.size();
	double suma_pib = 0;
	for (int i = 0; i < tam_p; ++i) {
		if (p[i].nom[0] == c) {
			int tam_provs = p[i].provs.size();
			for (int j = 0; j < tam_provs; ++j) {
				double hab = p[i].provs[j].habitants;
				double area =p[i].provs[j].area;
				if (hab/area > d) suma_pib += p[i].provs[j].pib;
			}
		}
	}
	return suma_pib;
}