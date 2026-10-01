#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


struct Paraula {
	string s;
	int rep;
};

typedef vector<Paraula> Llista_Paraules;


bool ordenar(const Paraula& v1,const Paraula& v2) {
	if (v1.rep > v2.rep) return true;
	if (v1.rep < v2.rep) return false;
	return (v1.s < v2.s);
}


//Pre:
//Post:
int main() {
	int n;
	while (cin >> n) {
		vector<string> v(n);
		for(int i = 0; i < n; ++i) cin >> v[i];
		sort(v.begin(),v.end());
		Llista_Paraules u(n);
		u[0].s = v[0];
		int k = 0;
		for (int i = 0; i < n; ++i) {
			if (u[k].s != v[i]) {
				++k;
			    u[k].s = v[i];
			    u[k].rep = 1;
			}
			else ++u[k].rep;
		}
		Llista_Paraules w(k+1);
		for (int i = 0; i < k+1; ++i) {
			w[i].s = u[i].s;
			w[i].rep = u[i].rep;
		}
		sort(w.begin(),w.end(),ordenar);
		for(int i = 0; i < k+1; ++i) cout << w[i].rep << " " << w[i].s << endl;
		cout << "----------" << endl;
	}
}
