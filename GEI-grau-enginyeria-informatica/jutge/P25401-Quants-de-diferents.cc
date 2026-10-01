#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void read_vector(vector<int>& v) {
	int tam = v.size();
	for (int i = 0; i < tam; ++i) {
		cin >> v[i];
	}
}


int main() {
	int n;
	while (cin >> n) {
		vector<int> v(n);
		read_vector(v);
		sort(v.begin(), v.end());
		int comp = v[0];
		int count = 1;
		for (int i = 0; i < n; ++i) {
			if (v[i] != comp) {
				++count;
				comp = v[i];
			}
		}
		cout << count << endl;
	}
}
