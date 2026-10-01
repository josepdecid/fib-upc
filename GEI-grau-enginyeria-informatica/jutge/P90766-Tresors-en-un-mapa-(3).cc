#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

typedef vector<char> Row;
typedef vector<Row> Graph;


int bfs(const Graph &G, int xx, int yy)
{
  Graph visited(G.size(), Row(G[0].size(), 'F'));
  queue< pair<int, int> >  Q;
  Q.push(make_pair(xx, yy));
  visited[xx][yy] = 'T';
  int count = 0;
  while (!Q.empty()) {
    pair<int, int> actual = Q.front();
    int x = actual.first;
    int y = actual.second;
    //Above
    if (y > 0 && visited[x][y-1] == 'F' && G[x][y-1] != 'X') {
      if (G[x][y-1] == 't') ++count;
      Q.push(make_pair(x, y-1));
      visited[x][y-1] = 'T';
    }
    //Below
    if (y < G[0].size() - 1 && visited[x][y+1] == 'F' && G[x][y+1] != 'X') {
      if (G[x][y+1] == 't') ++count;
      Q.push(make_pair(x, y+1));
      visited[x][y+1] = 'T';
    }
    //Left
    if (x > 0 && visited[x-1][y] == 'F' && G[x-1][y] != 'X') {
      if (G[x-1][y] == 't') ++count;
      Q.push(make_pair(x-1, y));
      visited[x-1][y] = 'T';
    }
    //Right
    if (x < G.size() - 1 && visited[x+1][y] == 'F' && G[x+1][y] != 'X') {
      if (G[x+1][y] == 't') ++count;
      Q.push(make_pair(x+1, y));
      visited[x+1][y] = 'T';
  }
    Q.pop();
  }
  return count;
}

int main()
{
  int n, m;
  cin >> n >> m;
  Graph G(n, Row(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> G[i][j];
  int x, y;
  cin >> x >> y;
  cout << bfs(G, x-1, y-1) << endl;
}
