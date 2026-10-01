#include <iostream>
using namespace std;


bool es_palindrom(const string& s) {
	int i = 0;
	int k = s.size();
	--k;
	while (i < k) {
		if (s[i] != s[k]) return false;
		++i;
		--k;
	}
	return true;
}