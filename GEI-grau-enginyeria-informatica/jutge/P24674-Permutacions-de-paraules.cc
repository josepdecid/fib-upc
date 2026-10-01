#include <bits/stdc++.h>
using namespace std;


void write_permutation(const vector<string> &v)
{
  cout << "(" << v[0];
  for (int i = 1; i < v.size(); ++i) {
    cout << "," << v[i];
  }
  cout << ")" << endl;
}


void backtrack(vector<string> &v, const vector<string> &words, vector<int> used, int it)
{
  if (it == v.size()) write_permutation(v);
  else {
    for (int i = 0; i < v.size(); ++i) {
      if (!used[i]) {
	used[i] = true;
	v[it] = words[i];
	backtrack(v, words, used, it+1);
	used[i] = false;
      }
    }
  }
}

int main()
{
  int n;
  cin >> n;
  vector<string> words(n);
  for (int i = 0; i < n; ++i) cin >> words[i];
  vector<string> v(n);
  vector<int> used(n);
  backtrack(v, words, used, 0);
}
