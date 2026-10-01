#include <iostream>
using namespace std;


//Pre: LLegeix series de parells de naturals
//Post: Escriu el natural més petit més gran que a i múltiple de b
int main() {
	int a, b, num = 0;
	while (cin >> a >> b) {
		++num;
		if (a%b == 0) cout << '#' << num << " : " << a << endl;
		else {
			a = a/b;
			cout << '#' << num << " : " << b*a + b << endl;
		}
	}
}