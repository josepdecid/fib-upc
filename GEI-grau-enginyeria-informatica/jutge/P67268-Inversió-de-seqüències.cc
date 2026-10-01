#include <iostream>
#include <vector>
using namespace std;


//Pre: Llegeix una seqüència
//Post: Escriu la seqüència invertida
int main() {
	int n;
	while (cin >> n) {
		vector<int> v(n);
		for (int i = 0; i < n; ++i) {
			cin >> v[i];
		}
		bool primer = true;
		for (int i = n-1; i >= 0; --i) {
			if (not primer) cout << ' ';
			else primer = false;
			cout << v[i];
		}
		cout << endl;
	}
}