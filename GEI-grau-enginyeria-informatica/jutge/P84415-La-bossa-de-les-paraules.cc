#include <iostream>
#include <map>
using namespace std;
 
int main() {
  string action, word;
  map<string,int> M;
  map<string,int>::iterator it;
  while (cin >> action) {
    if (action == "store") {
      cin >> word;
      it = M.find(word);
      if (it == M.end()) M.insert(make_pair(word, 1));
      else it->second += 1;
    }
    else if (action == "delete") {
      cin >> word;
      it = M.find(word);
      if (it != M.end()) {
    if (it->second > 1) it->second -= 1;
    else M.erase(it);
      }
    }
    else if (action == "minimum?") {
      if (M.empty()) cout << "indefinite minimum" << endl;
      else {
    cout << "minimum: " << M.begin()->first << ", " << M.begin()->second << " time(s)" << endl;
      }
    }
    else { //"maximum?"
      if (M.empty()) cout << "indefinite maximum" << endl;
      else {
    it = M.end();
    --it;
    cout << "maximum: " << it->first << ", " << it->second << " time(s)" << endl;
      }
    }
  }
}
 