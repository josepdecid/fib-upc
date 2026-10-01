#include <iostream>
using namespace std;


//Pre: Llegeix diversos naturals
//Post: Omple un rectangle d'NxM amb succecions de 9-0
int main() {
	int n, m, x, f;
	f = 0;
	while (cin >> n) {
		cin >> m;
		if (f != 0) cout << endl;
		x = 9;
		for (int i = n; i != 0; --i) {
			for (int j = m; j != 0; --j) {
				cout << x;
				if (x > 0) --x;
				else x = 9;
			}
			cout << endl;
		}
		++f;
	}
}