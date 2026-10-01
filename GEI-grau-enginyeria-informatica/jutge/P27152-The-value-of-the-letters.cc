#include <iostream>
using namespace std;


int main() {
	int count = 0;
	char c;
	while (cin >> c) {
		if (c == 'a' || c == 'e') count += 1;
		else if (c == 'o' || c == 's') count += 2;
		else if (c == 'd' || c == 'i' || c == 'n' || c == 'r') count += 3;
		else if (c == 'c' || c == 'l' || c == 't' || c == 'u') count += 4;
		else if (c == 'm' || c == 'p') count += 5;
		else if (c == 'k' || c == 'w') count += 7;
		else count += 6;
	}
	cout << count << endl;
}