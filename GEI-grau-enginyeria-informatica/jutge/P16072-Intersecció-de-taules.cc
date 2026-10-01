#include <iostream>
#include <vector>
using namespace std;

typedef vector<double> Row;

Row interseccio(const Row&v1, const Row&v2) {
	int s1 = v1.size();
	int s2 = v2.size();
	int s3;
	if (s1 > s2) s3 = s2;
	else s3 = s1;
	Row aux(s3);
	int i, j, k;
	i = j = k = 0;
	while (i < s1 and j < s2) {
		if (v1[i] > v2[j]) ++j;
		else if (v1[i] < v2[j]) ++i;
		else if (k == 0 or aux[k-1] != v1[i]) {
			aux[k] = v1[i];
			++i;
			++j;
			++k;
		}
		else {
			++i;
			++j;
		}
	}
	Row v3(k);
	for (i = 0; i < k; ++i) v3[i] = aux[i];
	return v3;
}

int main() {
	int n;
	cin >> n;
	Row v1(n);
	for (int i = 0; i < n; ++i) cin >> v1[i];
	int k;
	cin >> k;
	Row v2(k);
	for (int i = 0; i < k; ++i) cin >> v2[i];
	Row v3;
	v3 = interseccio(v1, v2);
	for (int i = 0; i < v3.size(); ++i) {
		if (i > 0) cout << ' ';
		cout << v3[i];
	}
	cout << endl;
}