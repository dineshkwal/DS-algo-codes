const int kLimit = 100001;
unordered_set<int> bridges;
vector<int> id(kLimit);
vector<int> lowlink(kLimit);
vector<bool> visited(kLimit, false);
int counter = 0;

void dfs(const vector<vector<pair<int, int>>>& graph, int u, int parent = -1)
{
	visited[u] = true;
	id[u] = counter++;
	lowlink[u] = id[u];

	for (const auto& edge : graph[u])
	{
	    const auto v = edge.first;
	    const auto z = edge.second;
	    
		if (!visited[v])
		{
			dfs(graph, v, u);
			lowlink[u] = min(lowlink[u], lowlink[v]);

			if (id[u] < lowlink[v])
			{
				bridges.emplace(z);
			}
		}
		else if (v != parent)
		{
			lowlink[u] = min(lowlink[u], id[v]);
		}
	}
}
