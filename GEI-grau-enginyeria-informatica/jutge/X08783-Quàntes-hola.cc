#include <iostream>
#include <string>
using namespace std;


//Pre: Llegeix una frase
//Post: Ens diu el nombre de "hola" que hi han
int main() {
  string h;
  int count = 0;
  while (cin >> h) {
  if (h == "hola") ++count;
  }
  cout << count << endl;
}