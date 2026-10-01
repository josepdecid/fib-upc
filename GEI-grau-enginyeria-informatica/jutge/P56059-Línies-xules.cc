#include <iostream>
#include <string>
using namespace std;


int main() {
	int k, x = 0, nx = 0;
	string s;
	while (cin >> k) {
		if (k%2 == 0) {
			++nx;
			while (k != 0) {
				cin >> s;
				--k;
			}
		}
		else {
			int pos = 0;
			string ini, mig, fin;
			cin >> s; 
			ini = s;
			int k1 = k-1;
			--k;
			while (k != 0) {
				++pos;
				cin >> s;
				if (pos == k1/2) mig = s;
				else if (pos == k1) fin = s;
				--k;
			}
			if (ini == mig && mig == fin) ++x;
			else ++nx;	
		}
	}
	if (x + nx == x) cout << "totes xules" << endl;
	else if (x + nx == nx) cout << "cap de xula" << endl;
	else cout << "dels dos tipus" << endl;
}