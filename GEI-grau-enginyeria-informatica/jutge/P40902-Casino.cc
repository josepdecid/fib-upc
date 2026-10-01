#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
  
    map<string, int> M;
    map<string, int>::iterator it;
    
    string name, action;
    int money;
    
    while (cin >> name >> action) {
      it = M.find(name);
      if (action == "enters") {
	if (it != M.end()) cout << name << " is already in the casino" << endl;
	else {
	  M.insert(make_pair(name, 0));
	}
      } 
      else if (action == "leaves") {
	if (it == M.end()) cout << name << " is not in the casino" << endl;
	else {
	  cout << name << " has won " << it->second << endl;
	  M.erase(it);
	}
      }
      else {
	cin >> money;
	if (it == M.end()) cout << name << " is not in the casino" << endl;
	else it->second += money;
      }
    }
    cout << "----------" << endl;
    for (it = M.begin(); it != M.end(); ++it) {
      cout << it->first << " is winning " << it->second << endl;
    }
}
