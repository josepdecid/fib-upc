#include <iostream>
using namespace std;


int factorial(int n) {
	int f = 1;
	for (int i = 1; i <= n; ++i) {
		f = f*i;
	}
	return f;
}

//Pre: Llegeix un natural
//Post: Calcula el factorial
int main() {
	int n;
	cin >> n;
	cout << factorial(n) << endl;
}