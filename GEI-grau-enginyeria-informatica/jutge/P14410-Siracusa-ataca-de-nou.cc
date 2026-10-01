#include <iostream>
using namespace std;


void convergeix(int n, int& k, int& lluny) {
	int p = k;
	for (int i = 1; i <= n; ++i) {
		k = 0;
		int j = i;
		while (j != 1) {
			if (j > lluny) lluny = j;
			if (j%2 == 0) j = j/2; 
			else j = 3*j + 1;
			++k;
		}
		if (k >= p) cout << i << endl;
	}
	cout << "S'arriba a " << lluny << '.' << endl; 
}

int main() {
	int n, p;
	cin >> n >> p;
	int k = p;
	int lluny = 1;
	convergeix(n, k, lluny);
}