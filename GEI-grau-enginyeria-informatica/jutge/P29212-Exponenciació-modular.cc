#include <iostream>
using namespace std;


//Right-to-left binary method
int calculate(int &b, int& e, int& m)
{
    if (m == 0) return 0;
    int result = 1;
    b = b % m;
    while (e > 0) {
      if (e%2 == 1) result = (result * b) % m;
      e = e >> 1;
      b = (b * b) % m;
    }
    return result;
}


int main()
{
  int b, e, m;
  while (cin >> b >> e >> m) {
    cout << calculate(b, e, m) << endl;
  }
}
