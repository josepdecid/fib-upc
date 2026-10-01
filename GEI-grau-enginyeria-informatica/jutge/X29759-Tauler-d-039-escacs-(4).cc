#include <iostream>
using namespace std;

//Pre: Llegeix un tauler d'escacs amb m monedes per casella
//Post: Obtenim monedes a caselles blanques, negres i la diferència
int main() {
	int n;
	char m;
	cin >> n;
	int b = 0, w = 0;
	for (int j = n; j != 0; --j) {
		for (int i = n; i != 0; --i) {
			cin >> m;
			if ((i + j)%2 == 0) w = w + (m - '0');
			else b = b + (m - '0');
		}
	}
	cout << w << '-' << b << " = " << w - b << endl;
}