#include <iostream>
#include <vector>
using namespace std;


int main() {
	int n, x;
	cin >> n;
	int aux = n;
	vector<int> ultim(n);
	int i = 0;
	while (n != 0) {
		cin >> x;
		--n;
		ultim[i] = x;
		++i;
	}
	int count = 0;
	for (int j = 0; j < aux-1; ++j) {
		if (ultim[j] == ultim[aux-1]) ++count;
	}
	cout << count << endl;
}