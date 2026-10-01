#include <iostream>
#include <vector>
using namespace std;


vector<double> fusio(const vector<double>& v1, const vector<double>& v2) {
	int tam_v1 = v1.size();
	int tam_v2 = v2.size();
	int tam_res = tam_v1 + tam_v2;
	vector<double> fus(tam_res);
	int i = 0, j = 0, k = 0;
	while (i < tam_v1 && j < tam_v2) {
		if (v1[i] < v2[j]) {
			fus[k] = v1[i];
			++i;
			++k;
		}
		else if (v2[j] < v1[i]) {
			fus[k] = v2[j];
			++j;
			++k;
		}
		else if (v2[j] == v1[i]) {
			fus[k] = v1[i];
			++i;
			fus[k+1] = v2[j];
			++j;
			k += 2;
		}
	}
	while (i < tam_v1) {
		fus[k] = v1[i];
		++i;
		++k;
	}
	while (j < tam_v2) {
		fus[k] = v2[j];
		++j;
		++k;
	}
	return fus;
}
