#include <iostream>
using namespace std;


char complement(char c) {
	if (c == 'G') return 'C';
	else if (c == 'T') return 'A';
	else if (c == 'A') return 'T';
	else return 'G';
}

int main() {
	char c;
	int es = 0;
	bool seq = false;
		while (not seq && cin >> c) {
			if (es == 0) {
				if (c == 'T') ++es;
			}
			else if (es == 1) {
				if (c == 'A') ++es;
				else if (c != 'A' or c != 'T') --es;
			}
			else if (es == 2) {
				if (c == 'G') ++es;
				else if (c == 'T') --es;
				else es = 0;
			}
			if (es == 3) seq = true;
		}
		if (seq) {
			while (cin >> c) cout << complement(c);
		}
	cout << endl;
}