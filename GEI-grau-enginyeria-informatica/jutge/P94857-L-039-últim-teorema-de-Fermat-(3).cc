#include <iostream>
#include <cmath>
using namespace std;
 

//Pre: Llegeix uns valors a, b, c i d que comprenen x i y
//Post: Escriu el nombre de solucions de l'equació x²+y²=z²
int main() {
    double a, b, c, d;
    while (cin >> a >> b >> c >> d) {
		int count = 0;
        for (double i = a; i <= b; ++i) {
           for (double j = c; j <= d; ++j) {
              double sol = (i*i) + (j*j);
              sol = sqrt(sol);
              double k = int(sol);
              sol = sol - k;
              if (sol == 0) ++count;
           }
       }
       cout << count << endl;
	}
}