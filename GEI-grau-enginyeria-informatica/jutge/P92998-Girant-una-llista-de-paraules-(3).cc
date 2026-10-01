#include <iostream>
#include <string>
using namespace std;


void girar_llista(int n) {
	string p;
	cin >> p;
	if (n > 1) girar_llista(--n);
	cout << p << endl;
} 

int main() {
	int x;
	cin >> x;
	if (x != 0) girar_llista(x);
}