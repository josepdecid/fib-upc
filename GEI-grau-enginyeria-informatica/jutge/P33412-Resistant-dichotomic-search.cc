#include <iostream>
#include <vector>
using namespace std;


bool resistant_search(double x, const vector<double>& v)
{
  if (v.size() == 0) return false;
  int l = 0, r = v.size() - 1, mid;
  while (l + 1 < r) {
    mid = (l+r)/2;
    if (v[mid] == x || v[mid-1] == x || v[mid+1] == x) return true;
    else if (v[mid] > x) r = mid;
    else l = mid;
  }
  return ((x == v[l]) || (x == v[r]));
}
