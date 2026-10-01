#include <iostream>
using namespace std;


//Pre: Llegeix una seqüència d'altures
//Post: La sortida val SI, si hi ha algun pic major que 3143(m)
int main() {
	int p, cim = 0;
	cin >> p;
	int primer, segon;
	segon = p;
	while (p != 0 && cim != 2) {
		primer = p;
		cin >> p;
		segon = p;
		if (cim == 0) {
			if (segon > primer && segon > 3143) ++cim;
		}
		else if (cim == 1) {
			if (primer > segon) ++cim;
			else cim = 0;
		}
	}
	if (p != 0 && cim == 2) cout << "SI" << endl;
	else cout << "NO" << endl;
}