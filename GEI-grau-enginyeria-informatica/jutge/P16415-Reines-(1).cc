#include <bits/stdc++.h>
using namespace std;

typedef int boolean;


class NReines {

private:
  int n; //#Queens and square size
  int count; //Possible ways
  vector<int> current_config;
  vector<boolean> column_marker;
  vector<boolean> l_diagonal_marker;
  vector<boolean> r_diagonal_marker;
  
  inline int diag1(int i, int j)
  {
    return n-j-1 + i;
  }
  
  inline int diag2(int i, int j)
  {
    return i + j;
  }
  
  void backtracking(int i) {
    if (i == n) {
      ++count;
    }
    else {
      for (int j = 0; j < n; ++j) {
	if (!column_marker[j] && !l_diagonal_marker[diag1(i, j)] && !r_diagonal_marker[diag2(i, j)]) {
	  current_config[i] = j;
	  column_marker[j] = l_diagonal_marker[diag1(i, j)] = r_diagonal_marker[diag2(i, j)] = true;
	  backtracking(i+1);
	  column_marker[j] = l_diagonal_marker[diag1(i, j)] = r_diagonal_marker[diag2(i, j)] = false;
	}
      }
    }
  }
  
public:
  
  NReines(int n) {
   this->n = n;
   count = 0;
   current_config = vector<int>(n);
   column_marker = vector<boolean>(n, false);
   l_diagonal_marker = vector<boolean>(2*n - 1, false);
   r_diagonal_marker = vector<boolean>(2*n - 1, false);
   backtracking(0);
   cout << count << endl;
  }
  
};

int main()
{
  int n;
  cin >> n;
  NReines N(n);
}
