#include <iostream>
#include <vector>
using namespace std;


int main() {
	int n;
	cin >> n;
	vector<int> v(2*n);
	for (int i = 1; i < 2*n; i += 2) {
		cin >> v[i];
	}
	for (int j = 0; j < 2*n - 1; j += 2) {
		cin >> v[j];
	}
	vector<int> s(n);
	int pos;
	for (int k = 0; k < 2*n; ++k) {
		pos = v[k];
		++k;
		s[pos] = v[k];
	}
	bool primer = true;
	for (int l = 0; l < n; ++l) {
		if (not primer) cout << ' ';
		cout << s[l];
		primer = false;
	}
	cout << endl; 
}