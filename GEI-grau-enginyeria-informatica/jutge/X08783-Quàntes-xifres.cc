#include <iostream>
using namespace std;


//Pre: Llegeix una seqüència de parells naturals
//Post: Escriu el nombre de xifres de n en base b
int main() {
	int b, n;
	while (cin >> b) {
		cin >> n;
		int count = 0;
			while (n != 0) {
				n = n/b;
				++count;
			}
			cout << count << endl;
	}
}