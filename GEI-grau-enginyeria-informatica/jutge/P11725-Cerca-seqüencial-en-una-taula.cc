#include <iostream>
#include <vector>
using namespace std;


bool hi_es(int x, const vector<int>& v) {
	int tam = v.size();
	for (int i = 0; i < tam; ++i) {
		if (v[i] == x) return true;
	}
	return false;
}