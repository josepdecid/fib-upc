#include <iostream>
#include <queue>
#include <vector>
using namespace std;


typedef vector<int> Adj;
typedef vector<Adj> Graph;


void topological_sort(Graph &G, vector<int> & v)
{
  int n = G.size();
  vector<int> sorted;
  priority_queue<int, vector<int>, greater<int> > pQ;
  for (int i = 0; i < n; ++i)
    if (v[i] == 0) pQ.push(i);
  while (!pQ.empty()) {
    int new_node = pQ.top(); pQ.pop();
    sorted.push_back(new_node);
    for (int i = 0; i < G[new_node].size(); ++i) {
      if (--v[G[new_node][i]] == 0) pQ.push(G[new_node][i]);
    }
  }
  cout << sorted[0];
  for (int i = 1; i < n; ++i) {
    cout << " " << sorted[i];
  } cout << endl;
}

int main()
{
  int n, m, x, y;
  while (cin >> n >> m) {
    Graph G(n);
    vector<int> v(n);
    for (int i = 0; i < m; ++i) {
      cin >> x >> y;
      G[x].push_back(y);
      ++v[y];
    }
    topological_sort(G, v);
  }
}
