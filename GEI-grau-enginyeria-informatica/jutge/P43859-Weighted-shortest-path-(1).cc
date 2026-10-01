#include <iostream>
#include <vector>
#include <queue>
using namespace std;


typedef pair<int, int> node_distance; // First -> Weight | Second -> Node
typedef vector< vector<node_distance> > Graph;
typedef int boolean;

int dijkstra(const Graph &G, int x, int y)
{
	vector<boolean> visited(G.size(), false);
	vector<int> distance(G.size(), -1); // We consider -1 as infinite
	priority_queue< node_distance, vector<node_distance>, greater<node_distance> > pQ;
	pQ.push({0, x});
	distance[x] = 0;
	while (!pQ.empty()) {
		int current_node = pQ.top().second;
		pQ.pop();
		if (!visited[current_node]) {
			visited[current_node] = true;
			for (int i = 0; i < G[current_node].size(); ++i) {
				node_distance aux = G[current_node][i];
				if (distance[aux.second] == -1 || distance[aux.second] > distance[current_node] + aux.first) {
					distance[aux.second] = distance[current_node] + aux.first;
					pQ.push({distance[aux.second], aux.second});
				}
			}
		}
	}
	return distance[y];
}

int main()
{
	int n, m;
	while (cin >> n >> m) {
		Graph G(n);
		int u, v, c;
		for (int i = 0; i < m; ++i) {
			cin >> u >> v >> c;
			G[u].push_back({c, v});
		}
		int x, y;
		cin >> x >> y;
		int result = dijkstra(G, x, y);
		if (result == -1) cout << "no path from " << x << " to " << y << endl;
		else cout << result << endl;
	}
}
