#include <iostream>
#include <vector>
using namespace std;


struct word {
  char c;
  bool b;
};


void writePermutation(const vector<char> &v, const int &n)
{
  for (int i = 0; i < n; ++i)
    cout << v[i];
  cout << endl;
}

void backtrack(vector<char> &v, const int &n, int it, vector<word> &s1, vector<word> &s2)
{
  if (it == n) writePermutation(v, n);
  else {
    if (it%2 == 0) { //Consonants
      for (int i = 0; i < n/2; ++i) {
	if (!s1[i].b) {
	  s1[i].b = true;
	  v[it] = s1[i].c;
	  backtrack(v, n, it+1, s1, s2);
	  s1[i].b = false;
	}
      }
    }
    else { //Vowels
      for (int i = 0; i < n/2; ++i) {
	if (!s2[i].b) {
	  s2[i].b = true;
	  v[it] = s2[i].c;
	  backtrack(v, n, it+1, s1, s2);
	  s2[i].b = false;
	}
      }
    }
  }
}

int main()
{
  int n;
  cin >> n;
  vector<word> s1(n);
  for (int i = 0; i < n; ++i)
    cin >> s1[i].c;
  vector<word> s2(n);
  for (int i = 0; i < n; ++i)
    cin >> s2[i].c;
  vector<char> v(2*n);
  backtrack(v, n*2, 0, s1, s2);
}
