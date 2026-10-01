#include <iostream>
#include <vector>
using namespace std;


int first_occurrence(double x, const vector<double>& v)
{
  int first = 0, last = v.size() - 1, it, mid;
  int size = v.size();
  while (size > 0) {
    it = first;
    mid = size/2;
    it += mid;
    if (v[it] < x) {
      first = ++it;
      size -= mid + 1;
    }
    else size = mid;
  }
  if (first < 0 || first >= v.size()) return -1;
  if (v[first] != x) return -1;
  return first;
}


int main()
{
  int n;
  cin >> n;
  vector<double> v(n);
  for (int i = 0; i < n; ++i) cin >> v[i];
  cin >> n;
  cout << first_occurrence(n, v) << endl;
}
