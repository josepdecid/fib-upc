#include <iostream>
using namespace std;

//Precondició: A guanya a P, P guanya a V i V guanya a A
//Postcondició: Retorna el guanyador

int main() {
  char p;
  cin >> p;
  if (p == 'A') {
    cin >> p;
    if (p == 'P') cout << 1 << endl;
    else if (p == 'V') cout << 2 << endl;
    else cout << '-' << endl;
  }else if (p == 'P') {
    cin >> p;
    if (p == 'A') cout << 2 << endl;
    else if (p == 'V') cout << 1 << endl;
    else cout << '-' << endl;
  }else {
    cin >> p;
    if (p == 'P') cout << 2 << endl;
    else if (p == 'A') cout << 1 << endl;
    else cout << '-' << endl;
  }
}