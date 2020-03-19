vector<int> lowlink(101);
vector<int> id(101);
vector<bool> visited(101, false);
vector<bool> isArticulation(101, false);
vector<int> parent(101, -1);
int counter = 0;

void dfs(vector<vector<int>>& graph, int u)
{
    visited[u] = true;
    id[u] = counter++;
    lowlink[u] = id[u];
    
    int numOutEdges = 0;
    
    bool articulation = false;
    
    for (auto v : graph[u])
    {
        if (!visited[v])
        {
            ++numOutEdges;
            parent[v] = u;
            
            dfs(graph, v);
            
            lowlink[u] = min(lowlink[u], lowlink[v]);
            
            if (id[u] <= lowlink[v])
            {
                articulation = true;
            }
        }
        else if (v != parent[u])
        {
            lowlink[u] = min(lowlink[u], id[v]);
        }
    }
    
    if ((parent[u] != -1 && articulation) || (parent[u] == -1 && numOutEdges > 1))
    {
        isArticulation[u] = true;   
    }
}