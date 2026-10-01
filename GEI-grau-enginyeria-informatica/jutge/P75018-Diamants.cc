#include <iostream>
#include <vector>
using namespace std;


void merge(vector<int> &v, int l, int r, int m)
{
	vector<int> B(r - l + 1);
	int i = l;
	int j = m + 1;
	int k = 0;
	while (i <= m and j <= r) {
		if (v[i] <= v[j]) B[k++] = v[i++];
		else B[k++] = v[j++];
	}
	while (i <= m) B[k++] = v[i++];
	while (j <= r) B[k++] = v[j++];
	for (k = 0; k <= r - l; ++k) v[l+k] = B[k];
}

void merge_sort(vector<int> &v, int l, int r)
{
	if (l < r) {
		int m = (l+r)/2;
		merge_sort(v, l, m);
		merge_sort(v, m+1, r);
		merge(v, l, r, m);
	}
}


bool check_add(vector<int> &v, int l, int r, int u)
{
	while (l < r) {
		if (v[l] + v[r] < u) {
			if (v[l] < v[r]) ++l;
			else --r;
		}
		else if (v[l] + v[r] > u) {
			if (v[l] > v[r]) ++l;
			else --r;
		}
		else return true;
	}
	return false;
}


int main()
{
	int u, n;
	while (cin >> u >> n && (u != 0 || n != 0)) {
		vector<int> v(n);
		for (int i = 0; i < n; ++i) cin >> v[i];
		merge_sort(v, 0, n-1);
		if (check_add(v, 0, n-1, u)) cout << "married" << endl;
		else cout << "single" << endl;	
	}
}
