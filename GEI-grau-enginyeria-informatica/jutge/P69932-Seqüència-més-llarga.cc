#include <iostream>
#include <string>
#include <set>
using namespace std;


int count_cons(set<int> &S1, set<int> &S2)
//This function calculates how many sequences can we find.
{
    if (S1.empty() && S2.empty()) return 0;
    else if (S1.empty() || S2.empty()) return 1;
    else {
      int count = 1, turn = 0, aux;
      set<int>::iterator it1 = S1.begin(), it2 = S2.begin();
      if (*it1 < *it2) {
	aux = *it1;
	++turn;
      }
      else aux = *it2;
      for(;;) {
	if (turn%2 == 0) {
	  while (it1 != S1.end() && *it1 < aux) ++it1;
	  if (it1 == S1.end()) return count;
	  else {
	    ++count;
	    ++turn;
	    aux = *it1;
	    ++it1;
	  }
	}
	else {
	  while (it2 != S2.end() && *it2 < aux) ++it2;
	  if (it2 == S2.end()) return count;
	  else {
	    ++count;
	    ++turn;
	    aux = *it2;
	    ++it2;
	  }
	}
      }
    }
}


int atoi(string &s)
//String to integer converter
{
  int k = 0;
  for (int i = 0; i < s.size(); ++i) {
    k = (k*10)+(s[i] - '0');
  }
  return k;
}


int main()
{
  string s;
  while (getline(cin,s)) {
    set<int> S1, S2;
    int n;
    string aux = "";		// aux atoi
    bool mto = false;		// More than one
    for (int i = 0; i < s.size(); ++i) {
      if (s[i] != ' ') {
	aux.insert(aux.end(), 1, s[i]);
      }
      else {
	n = atoi(aux);
	if (n%2 == 0) S1.insert(n);
	else S2.insert(n);
	aux = "";
	mto = true;
      }
    }
    if (mto) {
      n = atoi(aux);
      if (n%2 == 0) S1.insert(n);
      else S2.insert(n);
      cout << count_cons(S1, S2) << endl;
    }
    else { //If the line is empty or have just 1 number have to print this.
      if (s == "") cout << 0 << endl;
      else cout << 1 << endl;
    }
  }
}
