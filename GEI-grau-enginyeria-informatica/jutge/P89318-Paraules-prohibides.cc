#include <iostream>
#include <vector>
using namespace std;

typedef int boolean;

void print_case(const vector<char> &v, const int &n)
{
  for (int i = 0; i < n; ++i)
    cout << v[i];
  cout << endl;
}

void backtrack(vector<char> &v, vector<boolean> &used, const int &n, int it)
{
  if (it == n) print_case(v, n);
  else {
    for (int i = 0; i < n; ++i) {
      if (!used[i] && (it == 0 || v[it-1] + 1 != 'a' + i)) {
        used[i] = true;
        v[it] = 'a' + i;
        backtrack(v, used, n, it+1);
        used[i] = false;
      }
    }
  }
}

int main()
{
  int n;
  cin >> n;
  vector<boolean> used(n, false);
  vector<char> v(n);
  backtrack(v, used, n, 0);
}
