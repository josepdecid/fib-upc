#include <iostream>
using namespace std;


//Pre: Llegeix un natural n i n nombres
//Post: En calcula la variança
int main() {
  cout.setf(ios::fixed);
  cout.precision (2);
  double n, x, u = 0, v = 0;
  cin >> n;
  for (int i = n; i != 0; --i) {
    cin >> x;
    u = u + x*x;
    v = v + x;
  }
  v = v*v;
  u = (1 / (n-1))*u;
  v = (1 / (n*(n-1)))*v;
  cout << u-v << endl;
}