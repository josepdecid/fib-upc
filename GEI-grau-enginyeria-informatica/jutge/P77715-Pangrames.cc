#include <iostream>
#include <vector>
using namespace std;


int main() {
	char c;
	while (cin >> c) {
		if(c != '.') {
			vector<bool> v(26, false);
			if (c >= 'A' && c <= 'Z') v[int(c - 'A')] = true;
			else if (c >= 'a' && c <= 'z') v[int(c - 'a')] = true;
			while (cin >> c && c != '.') {
				if (c >= 'A' && c <= 'Z') v[int(c - 'A')] = true;
				else if (c >= 'a' && c <= 'z') v[int(c - 'a')] = true;
			}
			bool error = false;
			for (int i = 0; i < 26 && not error; ++i) {
				if (not v[i]) error = true;
			}
			if (not error) cout << "SI" << endl;
			else cout << "NO" << endl;
		}
		else cout << "NO" << endl;
	}
}
