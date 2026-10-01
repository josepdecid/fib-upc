#include <iostream>
using namespace std;


//Llegeix triplets de naturals
//Escriu la suma de 1/a + 1/a+k + 1/a+2k ... fins que el denominador sigui més gran que b
int main() {
	cout.setf(ios::fixed);
	cout.precision(4);
	double a, b, k;
	while (cin >> a >> b >> k) {
		double mult = 0;
		double sumfrac = 0;
		while ((a + mult*k) <= b) {
			sumfrac = sumfrac + (1/(a + mult*k));
			++mult;
		}
		cout << sumfrac << endl;
	}
}