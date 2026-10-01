#include <iostream>
#include <vector>
using namespace std;


int main() {
	int n, p, k;
	char c;
	cin >> n >> p >> k >> c;
	vector<string> v(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
	}
	int pos = p;
	if (c == 'd') {
		bool primer = true;
		for (int i = 0; i < k; ++i) {
			++pos;
			if (pos >= n) pos = 0;
			if (not primer) cout << ' ';
			cout << v[pos];
			primer = false;
		}
	}
	if (c == 'e') {
		bool primer = true;
		for (int i = 0; i < k; ++i) {
			--pos;
			if (pos < 0) pos = n-1;
			if (not primer) cout << ' ';
			cout << v[pos];
			primer = false;
		}
	}
	cout << endl;
}