#include <iostream>
using namespace std;


//Pre: Un natural n
//Post: Suma xifres parells, senars i la relació
int main() {
	int n, p = 0, s = 0;
	cin >> n;
	while (n != 0) {
		s = s + n%10;
		n = n/10;
		p = p + n%10;
		n = n/10;
	}
	cout << s << ' ' << p << endl;
	if (p >= s and s != 0) {
		if (p%s != 0) cout << "res" << endl;
		else cout << p << " = " << p/s << " * " << s << endl;
	}else if (s >= p and p != 0) {
		if (s%p != 0) cout << "res" << endl;
		else cout << s << " = " << s/p << " * " << p << endl;
	}else if (s == 0 or p == 0) {
		if (s == 0) cout << "0 = 0 * " << p << endl; 
		else if (p == 0) cout << "0 = 0 * " << s << endl;
	}
}