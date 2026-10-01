#include <iostream>
#include <vector>
using namespace std;


int merge(vector<int>& v, int l, int m, int r)
//Return inversions and merged vector v[l..r] = v[l..m] ~ v[m+1..r]
{
	vector<int> z(r-l+1);
	int i = l;
	int j = m+1;
	int k = 0;
	int count = 0;
	while (i <= m && j <= r) {
		if (v[i] <= v[j])
			z[k++] = v[i++];
		else {
			z[k++] = v[j++];
			count += m+1 - i;
		}
	}
	while (i <= m) z[k++] = v[i++];
	while (j <= r) z[k++] = v[j++];
	for (k = 0; k < z.size(); ++k) v[l+k] = z[k];
	return count;
}

int mergesort_inv(vector<int>& v, int l, int r)
//Return number of inversions of v[l..r]
//Total ammount of inversions will be inversions of left vector + right vector (recursivity) + merge process inversions
{
	int count = 0;
	if (l < r) {
		int m = (l+r)/2;
		count = mergesort_inv(v, l, m);
		count += mergesort_inv(v, m+1, r);
		count += merge(v, l, m, r);
	}
	return count;
}

int main()
{
	int n;
	while (cin >> n) {
		vector<int> v(n);
		for (int i = 0; i < n; ++i) cin >> v[i];
		cout << mergesort_inv(v, 0, v.size()-1) << endl;
	}
}
