#include <bits/stdc++.h>
using namespace std;


void write_permutation(const vector<int> &v)
{
  cout << "(" << v[0];
  for (int i = 1; i < v.size(); ++i) {
    cout << "," << v[i];
  }
  cout << ")" << endl;
}


void backtrack(vector<int> &v, vector<int> used, int it)
{
  if (it == v.size()) write_permutation(v);
  else {
    for (int i = 0; i < v.size(); ++i) {
      if (!used[i]) {
	used[i] = true;
	v[it] = i+1;
	backtrack(v, used, it+1);
	used[i] = false;
      }
    }
  }
}

int main()
{
  int n;
  cin >> n;
  vector<int> v(n);
  vector<int> used(n);
  backtrack(v, used, 0);
}
