#include <iostream>
using namespace std;


bool calculate() {
  char c;
  int count_par = 0;
  int count_cla = 0;
  bool par_open = false;
  bool cla_open = false;
  while (cin >> c && c != '.') {
    if (c == ')') {
      --count_par;
      if (cla_open) return false;
      par_open = false;
    }
    else if (c == ']') {
      --count_cla;
      if (par_open) return false;
      cla_open = false;
    }
    else if (c == '(') {
      ++count_par;
      par_open = true;
      cla_open = false;
    }
    else if (c == '[') {
      ++count_cla;
      par_open = false;
      cla_open = true;
    }
    if (count_par < 0 || count_cla < 0) {
	return false;
    }
  }
  return true;
}


int main() {
  if (!calculate()) cout << "Incorrecte" << endl;
  else cout << "Correcte" << endl;
}
