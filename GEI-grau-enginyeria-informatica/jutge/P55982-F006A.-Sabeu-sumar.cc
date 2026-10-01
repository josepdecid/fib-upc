#include <iostream>
#include <vector>
using namespace std;


string suma(string x, string y) {
	int tam_x = x.size();
	int tam_y = y.size();
	string z(tam_x + 1, '0');
	int carry = 0;
	for (int i = 0; i < tam_x; ++i) {
		int val = carry + x[tam_x - i - 1] - '0';
		if (i < tam_y) val += y[tam_y - i - 1] - '0';
		z[tam_x - i] = val%10 + '0';
		carry = val/10;
	}
	z[0] += carry;
	return z;
}


int main() {
	string x, y;
	while (cin >> x >> y) cout << suma(x,y) << endl;
}
