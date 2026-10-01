#include <iostream>
using namespace std;


//Pre: Llegeix el nombre de preguntes i la resposta a cada una
//Post: Obté la resposta més repetida i quantes n'hi ha
int main() {
  int n, ca, cb, cc;
  ca = cb = cc = 0;
  char x;
  cin >> n;
  while (n != 0) {
    cin >> x;
    if (x == 'a') ++ca;
    else if (x == 'b') ++cb;
    else if (x == 'c') ++cc;
    --n;
  }
  if (ca >= cb && ca >= cc) {
    cout << "majoria de a" << endl;
    cout << ca << " repeticio(ns)" << endl;
  }else if (cb >= ca && cb >= cc) {
    cout << "majoria de b" << endl;
    cout << cb << " repeticio(ns)" << endl;
  }else {
    cout << "majoria de c" << endl;
    cout << cc << " repeticio(ns)" << endl;
  }
}