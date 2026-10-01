#include <iostream>
#include <vector>
using namespace std;


int position(const vector<int> &S, const int a, int l, int r)
{
	if (l > r) return -1;
	else {
		int m = (l+r)/2;
		if (S[m]+a == m+1 && (m == 0 || m != S[m-1] + a)) return m+1;
		if (S[m]+a < m+1) return position(S, a, m+1, r);
		else return position(S, a, l, m-1);
	}	
}

void process_data(const vector<int> &S, const vector<int> &A)
{
	for (int i = 0; i < A.size(); ++i) {
		int pos = position(S, A[i], 0, S.size()-1);
		if (pos == -1) cout << "no fixed point for " << A[i] << endl;
		else cout << "fixed point for " << A[i] << ": " << pos << endl;
	}
	cout << endl;
}

void read_vector(vector<int> &v)
{
  int siz = v.size();
  for (int i = 0; i < v.size(); ++i)
    cin >> v[i];
}


int main()
{
    int n, count = 0;
    while (cin >> n) {
      cout << "Sequence #" << ++count << endl;
      vector<int> S(n);
      read_vector(S);
      cin >> n;
      vector<int> A(n);
      read_vector(A);
      process_data(S, A);
    }
}
