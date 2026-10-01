#include <iostream>
using namespace std;

//Precondició: Introduïm 3 nombres i l'ordre desitjat
//Postcondició: Obtenim els nombres ordenats

int main() {
  int x, y, z;
  cin >> x >> y >> z;
  string o;
  cin >> o; //ordre
  int A, B, C; //gran, mitjà, petit
  C = x;
  if (y > x) {
    if (z > y) {
      C = z;
      B = y;
      A = x;
    }else if (z < y && z > x) {
      C = y;
      B = z;
      A = x;
    }else {
      C = y;
      B = x;
      A = z;
    }
  }else {
    if (z > x) {
      C = z;
      B = x;
      A = y;
    }else if (z < x && z > y) {	
      B = z;
      A = y;
    }else {
      B = y;
      A = z;
    }
  }
  if (o == "ABC") cout << A << ' ' << B << ' ' << C << endl;
  if (o == "ACB") cout << A << ' ' << C << ' ' << B << endl;
  if (o == "BAC") cout << B << ' ' << A << ' ' << C << endl;
  if (o == "BCA") cout << B << ' ' << C << ' ' << A << endl;
  if (o == "CAB") cout << C << ' ' << A << ' ' << B << endl;
  if (o == "CBA") cout << C << ' ' << B << ' ' << A << endl;
}