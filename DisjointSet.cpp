#include <unordered_map>
#include <vector>

class DisjointSet
{
public:	
	// nodes from 1 to N
	DisjointSet(int N)
	{
		for (int i = 1; i <= N; ++i)
		{
			parent[i] = i;
			rank[i] = 0;
			size[i] = 1;
		}
	}

	// nodes as given in vector
	DisjointSet(const std::vector<int> v)
	{
		for (auto i : v)
		{
			parent[i] = i;
			rank[i] = 0;
			size[i] = 1;
		}
	}

	void Find(int i)
	{
		if (parent[i] != i)
		{
			parent[i] = Find(parent[i]);
		}

		return parent[i];
	}

	void UnionByRank(int i, int j)
	{
		const int pi = Find(i);
		const int pj = Find(j);
		if (pi == pj)
		{
			return; // already part of same set
		}

		const int ri = rank[pi];
		const int rj = rank[pj];
		if (ri == rj)
		{
			parent[pi] = pj;
			rank[pj]++;
		}
		else if (ri < rj)
		{
			parent[pi] = pj;
		}
		else
		{
			parent[pj] = pi;
		}
	}

	void UnionBySize(int i, int j)
	{
		const int pi = Find(i);
		const int pj = Find(j);
		if (pi == pj)
		{
			return; // already part of same set
		}

		const int si = size[pi];
		const int sj = size[pj];
		if (si <= sj)
		{
			parent[pi] = pj;
			size[pj] += size[pi];
		}
		else
		{
			parent[pj] = pi;
			size[pi] += size[pj];
		}
	}

private:
	std::unordered_map<int, int> parent;
	// use either union by rank or size
	std::unordered_map<int, int> rank;
	std::unordered_map<int, int> size;
};
