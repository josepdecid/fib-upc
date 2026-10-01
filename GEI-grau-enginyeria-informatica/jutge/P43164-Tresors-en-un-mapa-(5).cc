#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

typedef pair<int, int> Pos;
typedef int boolean;
typedef vector<boolean> Row;
typedef vector<Row> Graph;
typedef vector<char> Row2;
typedef vector<Row2> Matrix;


void bfs(Matrix &M, int x, int y)
{
  Graph distance(M.size(), Row(M[0].size(), 0));
  Graph visited(M.size(), Row(M[0].size(), false));
  queue<Pos> Q;
  stack<int> max_distances;
  Q.push(make_pair(x, y));
  while (!Q.empty()) {
    Pos new_pos = Q.front(); Q.pop();
    int i = new_pos.first;
    int j = new_pos.second;
    if (M[i][j] == 't') max_distances.push(distance[i][j]);
    //Add new nodes
    //Above
    if (i > 0 && !visited[i-1][j]) {
      visited[i-1][j] = true;
      if (M[i-1][j] != 'X') {
	distance[i-1][j] = distance[i][j] + 1;
	Q.push(make_pair(i-1, j));
      }
    }
    //Below
    if (i < M.size()-1 && !visited[i+1][j]) {
      visited[i+1][j] = true;
      if (M[i+1][j] != 'X') {
	distance[i+1][j] = distance[i][j] + 1;
	Q.push(make_pair(i+1, j));
      }
    }
    //Left
    if (j > 0 && !visited[i][j-1]) {
      visited[i][j-1] = true;
      if (M[i][j-1] != 'X') {
	distance[i][j-1] = distance[i][j] + 1;
	Q.push(make_pair(i, j-1));
      }
    }
    //Right
    if (j < M[0].size()-1 && !visited[i][j+1]) {
      visited[i][j+1] = true;
      if (M[i][j+1] != 'X') {
	distance[i][j+1] = distance[i][j] + 1;
	Q.push(make_pair(i, j+1));
      }
    }
  }
  if (max_distances.empty()) cout << "no es pot arribar a dos o mes tresors" << endl;
  else {
    max_distances.pop();
    if (max_distances.empty()) cout << "no es pot arribar a dos o mes tresors" << endl;
    else cout << "segona distancia maxima: " << max_distances.top() << endl;
  }
}

int main()
{
  int n, m, x, y;
  cin >> n >> m;
  Matrix M(n, Row2(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> M[i][j];
    }
  }
  cin >> x >> y;
  bfs(M, x-1, y-1);
}
