#include <iostream>
#include <vector>
using namespace std;

void write_vector(const vector<int> &v)
{
	if (v.size() != 0) {
		cout << v[0];
		for (int i = 1; i < v.size(); ++i)
			cout << " " << v[i];
	}
	cout << endl;
}

void find_combinations(vector<int> &v, int i, int my_ones, int &max_ones, int my_zeros, int &max_zeros)
{
	if (i == v.size()) {
		write_vector(v);
	}
	else {
		v[i] = 0;
		if (my_zeros < max_zeros) find_combinations(v, i+1, my_ones, max_ones, my_zeros+1, max_zeros);
		v[i] = 1;
		if (my_ones < max_ones) find_combinations(v, i+1, my_ones+1, max_ones, my_zeros, max_zeros);
	}
}


int main()
{
	int n, max_ones, max_zeros;
	cin >> n >> max_ones;
	max_zeros = n - max_ones;
	vector<int> v(n);
	find_combinations(v, 0, 0, max_ones, 0, max_zeros);
}
