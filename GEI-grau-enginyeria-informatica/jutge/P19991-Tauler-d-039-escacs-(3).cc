#include <iostream>
using namespace std;


//Pre: Llegeix un tauler d'escacs amb m monedes per casella
//Post: Obtenim la suma de monedes de les diagonals
int main () {
        int a, s, e, d;
        cin >> a;
        s=e=0;
        d=a-1;
        char n;
        for (int i=0; i<a; ++i) {
                for (int j=0; j<a; ++j) {
                        cin >> n;
                        if (j==e or j==d) s=s+(n-'0');
                }
                ++e;
                --d;
        }
        cout << s << endl;
}