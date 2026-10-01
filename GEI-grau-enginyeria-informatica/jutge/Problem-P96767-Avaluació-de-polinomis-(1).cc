#include <iostream>
using namespace std;


//Pre: Llegeix els coeficients ordenats d'una polinomi
//Post: La resol per a un valor
int main() {
	cout.setf(ios::fixed);
	cout.precision(4);
	double x, n, p=1, r;
	cin >> x >> r;
	while (cin >> n) {
		p = p*x;
		r = r + n*p;
	}
	cout << r << endl;
}