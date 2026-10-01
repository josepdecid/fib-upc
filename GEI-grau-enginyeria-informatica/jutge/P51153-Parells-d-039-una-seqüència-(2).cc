#include <iostream>
#include <vector>
using namespace std;


//Pre: Llegeix seqüències de naturals
//Post: Escriu si o no a cada una si té dos elements la suma dels quals es senar
int main() {
	int n; 
	while (cin >> n) {
		vector<int> v(n);
		for (int i = 0; i < n; ++i) {
			cin >> v[i];
		}
		bool senar = false;
		bool parell = false;
		int i = 0;
		while ((i < n) && (not senar or not parell)) {
			if (v[i]%2 == 0) parell = true;
			else if (v[i]%2 == 1) senar = true;
			++i;
		}
		if (parell*senar == 1) cout << "si" << endl;
		else cout << "no" << endl;
	}
}