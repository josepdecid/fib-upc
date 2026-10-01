#include <iostream>
#include <vector>
using namespace std;

const int MAX = 10000;

struct Data {
	int dia, mes, any;
};

typedef vector<Data> Dates;

Data data_llegida() {
	Data d;
	char c;
	cin >> d.dia >> c >> d.mes >> c >> d.any;
	return d;
}

int comp(const Data& a, const Data& b) {
	return a.any*10000 + a.mes*100 + a.dia - b.any*10000 - b.mes*100 - b.dia;
}

//Retorna la pos de x en v 
int cerca(int esq, int dre, const Data& x, const Dates& v) {
	int mig = (esq + dre) / 2;
	int c = comp(x, v[mig]);
	if (c < 0) return cerca(esq, mig - 1, x, v);
	if (c > 0) return cerca(mig + 1, dre, x ,v);
	return mig;
}


//Pre: Llegeix una seqüència d'addició eliminació o comparació de dates
//Post: Escriu la distància entre dues dates al comparar
int main() {
	Dates v(MAX);
	int n = 0;
	char c;
	while (cin >> c) {
		if (c == 'A') {
			v[n] = data_llegida();
			++n;
		}
		else if (c == 'E') --n;
		else {
			Data a = data_llegida();
			Data b = data_llegida();
			cout << cerca(0, n - 1, b, v) - cerca(0, n - 1, a, v) << endl;
		}
	}
}