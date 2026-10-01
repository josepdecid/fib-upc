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

void find_combinations(vector<int> &v, int i)
{
	if (i == v.size()) {
		write_vector(v);
	}
	else {
		v[i] = 0;
		find_combinations(v, i+1);
		v[i] = 1;
		find_combinations(v, i+1);
	}
}


int main()
{
	int n;
	cin >> n;
	vector<int> v(n);
	find_combinations(v, 0);
}
