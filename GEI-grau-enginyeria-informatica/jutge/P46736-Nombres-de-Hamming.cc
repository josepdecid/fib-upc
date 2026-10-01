#include <iostream>
using namespace std;


bool es_de_hamming(int x) {
	if (x== 1) return true;
	else if (x%2 == 0) return es_de_hamming(x/2);
	else if (x%3 == 0) return es_de_hamming(x/3);
	else if (x%5 == 0) return es_de_hamming(x/5);
	else return false;
}

//Pre: Llegeix una seqüència de naturals
//Post: Per cada n escriu els n primers nombres de Hamming
int main() {
	int n;
	while (cin >> n) {
		if (n > 0) {
			int i = 1;
			cout << i;
			--n;
			++i;
			while (n > 0) {
				if (es_de_hamming(i)) {
					cout << ',' << i;
					--n;
				}
				++i;
			}
		}
		cout << endl;
	}
}