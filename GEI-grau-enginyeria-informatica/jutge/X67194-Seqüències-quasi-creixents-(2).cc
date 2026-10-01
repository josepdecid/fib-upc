#include <iostream>
using namespace std;


void info_sequencia(int n, bool& es_qc, int& p_qc) {
	if (n <= 2) {
		for (int i = n; i != 0; --i) cin >> n;
		cout << p_qc << endl;
	}
	else {
		int primer, segon = 0, tercer = 0;
		int aux = n - 3;
		for (int i = 3; i != 0; --i) {
			primer = segon;
			segon = tercer;
			cin >> n;
			tercer = n;
		}
		if (primer >= segon && primer >= tercer) es_qc = false;
		if (es_qc) ++p_qc;
		while (aux != 0) {
			primer = segon;
			segon = tercer;
			cin >> n;
			tercer = n;
			if (primer >= segon && primer >= tercer) es_qc = false;
			if (es_qc) ++p_qc;
			--aux;
		}
		cout << p_qc << endl;
	}
}

//Pre: Llegeix diverses seqüències de naturals
//Post: Escriu la posició de quasi-creixement i el total de seq. quasi creixents
int main() {
	int n;
	int count = 0;
	while (cin >> n && n != 0) {
		bool es_qc = true;
		int p_qc = 2;
		info_sequencia(n, es_qc, p_qc);
		if (es_qc) ++count;
	}
	cout << "Quasi-creixents: " << count << endl;
}