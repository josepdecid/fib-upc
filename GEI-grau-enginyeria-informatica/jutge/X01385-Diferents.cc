#include <iostream>
#include <vector>
using namespace std;

int diferents(vector <int> &v) {
  int cont=0;
  int n = v.size();
  for (int i=0; i<n; ++i) {
    cin >> v[i];
    int k=0;
    bool trobat = false;
    while (k<i and not trobat) {
      if (v[k] == v[i]) {
	trobat = true;
      }
      ++k;
    }
    if (not trobat) ++cont;
  }
  return cont;
}

int main() {
  int n;
  while (cin >> n) {
    vector <int> v(n);
    int result = diferents(v);
    cout << result << endl;
  }
}