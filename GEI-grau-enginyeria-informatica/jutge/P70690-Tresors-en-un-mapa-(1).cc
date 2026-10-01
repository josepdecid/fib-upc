#include <iostream>
#include <vector>
using namespace std;


typedef vector<char> Node;
typedef vector<Node> Graph;

void dfs_rec(const Graph &G, int x, int y, Graph &visited, bool &found)
{
  if (visited[x][y] == 'F' && !found) {
    visited[x][y] = 'T';
    if (G[x][y] == 't') found = true;
    else if (G[x][y] != 'X') {
      if (y != G[0].size() - 1) dfs_rec(G, x, y+1, visited, found); //Right
      if (x != G.size() - 1) dfs_rec(G, x+1, y, visited, found); //Below
      if (y != 0) dfs_rec(G, x , y-1, visited, found); //Left
      if (x != 0) dfs_rec(G, x-1, y, visited, found); //Above
    }
  }
}


int main()
{
  int n, m;
  cin >> n >> m;
  int total_size = n*m;
  Graph G(n, Node(m))	;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> G[i][j];
  int x, y;
  cin >> x >> y;
  Graph visited(n, Node(m, 'F'));
  bool found = false;
  dfs_rec(G, x-1, y-1, visited, found);
  if (found) cout << "yes" << endl;
  else cout << "no" << endl;
}
