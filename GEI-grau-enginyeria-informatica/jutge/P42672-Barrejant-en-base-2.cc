#include <iostream>
using namespace std;

//Barrejar es escriure una xifra de cada nombre
void canvi_i_barreja(int a, int b) {
    if (a != 0 or b != 0) {
        canvi_i_barreja(a/2, b/2);
        cout << a%2;
        cout << b%2;
    }
}

//Pre: Llegeix 2 enters
//Post: Els converteix a binari i els barreja
int main(){
    int a, b;
    while (cin >> a >> b) {
        canvi_i_barreja(a, b);
        cout << endl;
    }
}