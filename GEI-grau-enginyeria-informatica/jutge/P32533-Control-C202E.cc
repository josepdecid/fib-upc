#include <iostream>
using namespace std;


//Pre: introduïm un natural
//Post: retorna una figura de n*n
int main() {
  int n;
  cin >> n;
  for (int i=n; i != 0; --i) {
    for (int j=i-1; j != 0; --j) cout << '+';
    cout << '/';
    for (int k=i; k != n; ++k) cout << '*';
    cout << endl;
  }
}