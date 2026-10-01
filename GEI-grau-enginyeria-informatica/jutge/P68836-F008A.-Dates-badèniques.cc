#include <iostream>
using namespace std;


struct Data {
	int dia, mes, any;
};

void llegir_data(Data& x) {
	char c;
	cin >> x.dia >> c >> x.mes >> c >> x.any;
}

bool menor(const Data& d1, const Data& d2) {
	if (d1.any < d2.any) return true;
	else if (d1.any == d2.any) {
		if (d1.mes < d2.mes) return true;
		else if (d1.mes == d2.mes) {
			if (d1.dia < d2.dia) return true;
		}
	}
	return false;
}


//Pre: Llegeix un nombre n i n dates de estrutura indefinida
//Post: Escriu quina es la primera data que esta  compresa entre l'anterior i la següent
int main() {
	int n;
	cin >> n;
	Data d1, d2;
	llegir_data(d2);
	--n;
	bool cond1 = false, cond2 = false; //Ordre dates creixent
	bool cond3 = false, cond4 = false; //Ordre dates decreixent
	bool trobat = false;
	while (not trobat && n != 0) {
		d1.any = d2.any;
		d1.mes = d2.mes;
		d1.dia = d2.dia;
		llegir_data(d2);
		//d1 > dx > d2
		if (not cond3 && not menor(d1, d2)) cond3 = true;
		else if (cond3 && not menor(d1, d2)) cond4 = true;
		else if (cond3 && menor(d1, d2)) cond3 = false;
		//d1 < dx < d2
		if (not cond1 && menor(d1, d2)) cond1 = true;
		else if (cond1 && menor(d1, d2)) cond2 = true;
		else if (cond1 && not menor(d1, d2)) cond1 = false;
		//Veredicte
		if ((cond1 && cond2) || (cond3 && cond4)) trobat = true;
		--n;
	}
	if (trobat) cout << d1.dia << "/" << d1.mes << "/" << d1.any << endl;
	else cout << "cap data trobada" << endl;
}