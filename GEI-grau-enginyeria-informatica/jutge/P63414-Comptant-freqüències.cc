#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
	int n;
	cin >> n;
	if (n > 0) {
		vector<int> v(n);
		for (int i = 0; i < n; ++i) {
			cin >> v[i];
		}
		sort(v.begin(),v.end());
		int comp = v[0];
		int count = 0;
		for (int i = 0; i < n; ++i) {
			if (v[i] == comp) ++count;
			else {
				cout << comp << " : " << count << endl;
				count = 1;
				comp = v[i];
			}
		}
		cout << comp << " : " << count << endl;
	}
}