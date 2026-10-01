#include <iostream>
using namespace std;

//Precondició: Llegeix anys, dies, hores, minuts i segons
//Postcondició: Converteix tot a segons i ho suma

int main() {
  int a, d, h, m, s;
  cin >> a >> d >> h >> m >> s;
  cout << s+60*m+3600*h+3600*24*d+3600*24*365*a << endl;
}