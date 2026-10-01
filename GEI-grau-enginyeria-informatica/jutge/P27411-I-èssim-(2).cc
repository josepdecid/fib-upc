#include<iostream>
#include<vector>
using namespace std;


//Pre: Legeix n i una seqüència de naturals x
//Post: Escriu quina x hi ha a la posició n
int main() {
    vector <int> v;
    int x;
    cin >> x;
    int n;
    while (cin >> n and n != -1) v.push_back(n);
    if (x < 1 or x > v.size()) cout << "Posicio incorrecta." << endl;
    else cout << "A la posicio " << x << " hi ha un " << v[x - 1] << "." << endl;
}