#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

struct stats {
  bool connected;
  int elo;
};

bool compare_score(pair<int, string> p1, pair<int, string> p2) {
  if (p1.first > p2.first) return true;
  else {
    if (p1.first < p2.first) return false;
    else return (p1.second < p2.second);
  }
}

int main() {
    string action, p1, p2;
    stats s;
    map<string, stats> M;
    map<string, stats>::iterator it;
    while (cin >> action) {
      cin >> p1;
      it = M.find(p1);
      if (action == "LOGIN") {
	if (it == M.end()) {
	  s.connected = true;
	  s.elo = 1200;
	  M.insert(make_pair(p1, s));
	}
	else {
	  it->second.connected = true;
	}
      }
      else if (action == "LOGOUT") {
	if (it != M.end()) {
	  it->second.connected = false;
	}
      }
      else if (action == "GET_ELO") {
	cout << it->first << " " << it->second.elo << endl;
      }
      else {
	cin >> p2;
	map<string, stats>::iterator it2 = M.find(p2);
	if ((it != M.end() && it2 != M.end()) && (it->second.connected && it2->second.connected)) {
	  it->second.elo += 10;
	  it2->second.elo -= 10;
	  if (it2->second.elo < 1200) it2->second.elo = 1200;
	}
	else cout << "jugador(s) no connectat(s)" << endl;
      }
    }
    cout << endl << "RANKING" << endl;
    int tam = M.size();
    vector< pair<int,string> > v(tam);
    int i = 0;
    for (it = M.begin(); it != M.end(); ++it) {
      v[i].first = it->second.elo;
      v[i].second = it->first;
      ++i;
    }
    sort(v.begin(), v.end(), compare_score);
    for (i = 0; i < v.size(); ++i) {
      cout << v[i].second << " " << v[i].first << endl;
    }
}
