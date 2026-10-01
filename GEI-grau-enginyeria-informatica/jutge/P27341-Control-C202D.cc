#include <iostream>
using namespace std;


//Pre: Llegeix 2 nombres enters;
//Post: N'obtenim la suma dels cubs de tots els nombres entre a i b
int main() {
  int a, b, s, p;
  while (cin >> a >> b) {
    if (a <= b) {
      s = 0;
      for (int i = a; i != b+1; ++i) {
	p = i;
	for (int j = 2; j != 0; --j) {
	  p = p*i;
	}
	s = s+p;
      } 
      cout << "suma dels cubs entre " << a << " i " << b << ": " << s << endl;
    }else cout << "suma dels cubs entre " << a << " i " << b << ": " << 0 << endl;
  }
}