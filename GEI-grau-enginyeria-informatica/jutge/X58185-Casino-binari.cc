#include <iostream>
#include <vector>
#include <string>
using namespace std;


int main() {
  int e;
  char c;
  string nom;
  int ap, alt;
  cin >> e;
  
  int count_z = 0;
  int count_u = 0;
  int count_a = 0;
  bool first = true;
  int aux;
  while (cin >> c && c != '.') {
    
    if (c == '0') ++count_z;
    else ++count_u;
    
    if (first) {
      if (c == '0') aux = 0;
      else aux = 1;
      first = false;
    }
    else {
      if (aux == 0 && c == '1') {
	 ++count_a;
	 aux = 1;
      }
      else if (aux == 1 && c == '0') {
	 ++count_a;
	 aux = 0;
      }
    }
  }
  cout << count_z << " ceros" << endl;
  cout << count_u << " uns" << endl;
  cout << count_a << " alternancies" << endl;
  int aposta_guanyadora = 2;
  bool trobat = false;;
  if (count_z > count_u) aposta_guanyadora = 0;
  else if (count_z < count_u) aposta_guanyadora = 1;  
  else {
    cout << "Casino guanya 50% apostes" << endl << "50% apostes al pot" << endl;
    trobat = true;
  }
  while (!trobat && cin >> nom >> ap >> alt) {
    if (ap == aposta_guanyadora) {
      trobat = true;
      if (alt <= count_a + e && alt >= count_a - e) cout << nom << " guanya 50% apostes" << endl << nom << " guanya pot actual" << endl;
      else cout << nom << " guanya 50% apostes" << endl;
      cout << "50% apostes al pot" << endl;
    }
  }
  if (!trobat) {
    cout << "100% apostes al pot" << endl;
  }
}
