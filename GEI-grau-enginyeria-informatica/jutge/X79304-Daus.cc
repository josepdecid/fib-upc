#include <iostream>
#include <vector>
using namespace std;


void read_vector(vector<int>& v) {
  for (int i = 0; i < 5; ++i) {
    cin >> v[i];
  }
}

int operation(const vector<int>& v) {
  vector<int> aux(6, 0);
  int n;
  for (int i = 0; i < 5; ++i) {
    int j = v[i] - 1;
    ++aux[j];
  }  
  
  bool trobat = false;
  bool trio_provisional = false;
  bool parella_provisional = false;
  for (int i = 0; i < 6 && !trobat; ++i) {
    if (aux[i] >= 4) {
      trobat = true;
      n = 1;
    }
    else if (aux[i] == 3) {
      if (!parella_provisional) trio_provisional = true;
      else {
	trobat = true;
	n = 4;
      }
    }
    else if (aux[i] == 2) {
      if (parella_provisional) {
	trobat = true;
	n = 2;
      }
      else if (trio_provisional) {
	trobat = true;
	n = 4;
      }
      else parella_provisional = true;
    }
  }
  if (!trobat && parella_provisional) n = 5;
  else if (!trobat && trio_provisional) n = 3;
  else if (!trobat) n = 0;
  
  return n;
}

void result(int n) {
  if (n == 0) cout << "escala" << endl;
  else if (n == 1) cout << "poker" << endl;
  else if (n == 2) cout << "doble-parella" << endl;
  else if (n == 3) cout << "trio" << endl;
  else if (n == 4) cout << "full" << endl;
  else cout << "parella" << endl;
}

int main() {
  int n;
  cin >> n;
  vector<int> v(5);
  while (n != 0) {
    read_vector(v);	
    result(operation(v));
    --n;
  }
}
