#include <iostream>
#include <string>
using namespace std;


//Pre: Llegeix diverses seqüències de paraules
//Post: Et diu quina és la primera que està ordenade lexicogràficament
int main() {
	string prev, next;
	int n;
	int i = 0;
	bool found = false;
	while (cin >> n and not found){
		++i;
		found = true;
		cin >> prev;
		for (int c = 2; c <= n; ++c){
			cin >> next;
			if (next < prev) found = false;
			prev = next;
		}
		if (found) cout << "La primera linia ordenada creixentment es la " << i << "." << endl;
	}
	if (not found) cout << "No hi ha cap linia ordenada creixentment." << endl;
}