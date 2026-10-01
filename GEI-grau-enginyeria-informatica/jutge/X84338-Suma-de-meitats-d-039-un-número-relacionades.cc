#include <iostream>
using namespace std;


//Pre: Llegeix un natural
//Post: Si té xifres parells, compara la part esquerra i dreta
int main() {
	int n, xf = 0, a  = 0, b = 0;
	cin >> n;
	for (int i = n; i != 0; i = i/10) ++xf;
	if (xf%2 != 0 or n == 0) cout << "res" << endl;
	else {
		xf = (xf/2);
		for (int at = xf; at != 0; --at) {
			a = a + n%10;
			n = n/10;
		}
		for (int bt = xf; bt != 0; --bt) {
			b = b + n%10;
			n = n/10;
		} 
		if (a > b) cout << b << " < " << a << endl;
		else if (a < b) cout <<  b << " > " << a << endl;
		else cout << b << " = " << a << endl;
	}

}