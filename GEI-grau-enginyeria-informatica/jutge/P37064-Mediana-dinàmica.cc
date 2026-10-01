#include <iostream>
#include <set>
using namespace std;


int main() {
  set<string> v;
  set<string>::iterator it, mid;
  it = v.begin();
  string s;
  cin >> s;
  if (s != "END") {
    it = v.insert(it, s);
    cout << s << endl;
    mid = v.begin();
    while (cin >> s && s != "END") {
      v.insert(it, s);
      if (s < *mid && v.size()%2 == 0) --mid;
      else if (s > *mid && v.size()%2 != 0) ++mid;
      cout << *mid << endl;
    }
  }
}
