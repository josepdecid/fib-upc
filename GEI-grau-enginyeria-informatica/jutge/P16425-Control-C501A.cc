#include <iostream>
#include <vector>
using namespace std;

void primers(vector<int>& Primers) {;
    int cont = 0;
    for (int i = 2; i <= 7919; ++i) {
        bool primer = true;
        int j = 2;
        while (primer and j*j <= i) {
            if (i%j == 0) primer = false;
            ++j;
        }
        if (primer) {
            Primers[cont] = i;
            ++cont;
        }
    }
}

int main() {
    int n;
    vector<int> Primers(1000,0);
    primers(Primers);
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            cout << Primers[i];
            if (i < n - 1) cout << ",";
        }
        cout << endl;
    }
}
