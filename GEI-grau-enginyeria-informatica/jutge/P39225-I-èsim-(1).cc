#include <iostream>
using namespace std;


//Pre: Legeix n i una seqüència de naturals x
//Post: Escriu quina x hi ha a la posició n
int main() {
	int p, n;
	cin >> p;
	cout << "A la posicio " << p << " hi ha un ";
	while (p != 0) {
		cin >> n;
		--p;
	}
	cout << n << '.' << endl;
}