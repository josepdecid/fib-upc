#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <limits>
using namespace std;

typedef vector< pair<int, int> > Adj; // Distance - node
typedef vector<Adj> Graph;

typedef int boolean;

void dijkstra(Graph &G, int u, int v)
{
  int n = G.size();
  vector<int> distance(n, numeric_limits<int>::max()); // Infinite
  distance[u] = 0;
  vector<boolean> visited(n, false);
  vector<int> whereFrom(n, -1);
  priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pQ;
  pQ.push({0, u});
  while (!pQ.empty() && pQ.top().second != v) {
    int new_node = pQ.top().second;
    pQ.pop();
    if (!visited[new_node]) {
      visited[new_node] = true;
      for (int i = 0; i < G[new_node].size(); ++i) {
	pair<int, int> aux = G[new_node][i];
	if (distance[new_node] + aux.first < distance[aux.second]) {
	  distance[aux.second] = distance[new_node] + aux.first;
	  whereFrom[aux.second] = new_node;
	  pQ.push({distance[aux.second], aux.second});
	}
      }
    }
  }
  if (pQ.empty()) {
    cout << "no path from " << u << " to " << v << endl;
    return;
  }
  stack<int> result;
  while (whereFrom[v] != -1) {
    result.push(v);
    v = whereFrom[v];
  }
  result.push(v);
  cout << result.top(); result.pop();
  while (!result.empty()) {
    cout << " " << result.top();
    result.pop();
  }
  cout << endl;
}

int main()
{
  int n, m, u, v, c;
  while (cin >> n >> m) {
    Graph G(n);
    for (int i = 0; i < m; ++i) {
      cin >> u >> v >> c;
      G[u].push_back({c, v});
    }
    cin >> u >> v;
    dijkstra(G, u, v);
  }
}
