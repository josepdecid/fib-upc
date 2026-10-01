#include <iostream>
#include <map>
using namespace std;


int main() {
  int x, y, n;
  while (cin >> x >> y >> n) {
    map<int,int> M;
    map<int,int>::iterator it;
    int i = 0;
    bool found = false;
    M.insert(make_pair(n, i));
    while (n <= 100000000 && !found) {
      ++i;
      if (n%2 == 0) n = n/2 + x;
      else n = 3*n + y;
      it = M.find(n);
      if (it == M.end()) M.insert(make_pair(n, i));
      else found = true;
    }
    if (found) cout << (M.size() - it->second) << endl;
    else cout << n << endl;
  }
}
