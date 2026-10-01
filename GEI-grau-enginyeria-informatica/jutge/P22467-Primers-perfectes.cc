#include <iostream>
using namespace std;


bool primer(int a) {
	if (a <= 1) return false;
	for (int i = 2; i*i <= a; ++i) {
		if (a%i == 0) return false;
	}
	return true; 
}

bool es_primer_perfecte(int n) {
	if (not primer(n)) return false;
	int resultat = 0;
	int digits = 0;
	while (n > 0) {
		resultat = resultat + n%10;
		n = n/10;
		++digits;
	}
	bool resultat_primer = primer(resultat);
	if (resultat_primer && digits == 1) return true;
	else if (resultat_primer) return es_primer_perfecte(resultat);
	else return false;
}


//Pre: Llegeix un natural n
//Post: Retorna si totes les xifres son nombres primers
int main() {
	int n;
	while (cin >> n) {
		cout << es_primer_perfecte(n) << endl;
	}
}