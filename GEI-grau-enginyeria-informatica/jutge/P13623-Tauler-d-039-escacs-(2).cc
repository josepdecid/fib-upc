#include <iostream>
using namespace std;

//Pre: Llegeix un tauler amb n monedes per casella
//Post: Obtenim la suma de monedes a caselles blanques
int main () {
        int a, b, s;
        cin >> a >> b;
        s=0;
        char n;
        for (int i=0; i<a; ++i) {
                for (int j=0; j<b; ++j) {
                        cin >> n;
                        if (i%2==j%2) s=s+(n-'0');
                }
        }
        cout << s << endl;
}