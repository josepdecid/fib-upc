#include <iostream>
#include <vector>
using namespace std;


pair<int, int> find_vector(vector<int>& v) {
  int tam = v.size();
  pair<int, int> res;
  res.first = res.second = v[0];
  for (int i = 1; i < tam; i++) {
    if (v[i] > res.first) res.first = v[i];
    else if (v[i] < res.second) res.second = v[i];
  }
  return res;
}


int main() {
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i];
  pair<int, int> res = find_vector(v);
  cout << res.first << " " << res.second << endl;
}
