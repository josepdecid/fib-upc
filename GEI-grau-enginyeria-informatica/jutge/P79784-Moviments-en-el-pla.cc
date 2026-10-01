#include <iostream>
using namespace std;


//Pre: Llegeix una seqüència de coordenades
//Post: Obté la posició final
int main() {
  char c;
  int x, y; //Representa les posicions en un eix de coordenades
  x = 0;
  y = 0;
  while (cin >> c) {
    if (c == 'n') --y; //nord
    else if (c == 's') ++y; //sud
    else if (c == 'e') ++x; //est
    else if (c == 'o') --x; //oest
  }
  cout << '(' << x << ", " << y << ')' << endl;
}