#include<bits/stdc++.h>
using namespace	std;

class DisjointSet {
public:
	vector<int> parent, size, rank;
	DisjointSet(int n) {
		parent.resize(n + 1);
		size.resize(n + 1, 1);
		rank.resize(n + 1);
		for (int i = 0; i <= n; i++)
			parent[i] = i;
	}
	int findPar(int u) {
		if (u == parent[u])
			return u;
		return parent[u] = findPar(parent[u]);
	}
	void unionByRank(int u, int v)
	{
		int pu = findPar(u);
		int pv = findPar(v);
		if (pu == pv)
			return ;
		if (rank[pu] < rank[pv])
		{
			parent[pu] = pv;
		}
		else if (rank[pv] > rank[pu])
		{
			parent[pv] = pu;
		}
		else
		{
			parent[pv] = pu;
			rank[pu]++;
		}
	}
	void unionBySize(int u, int v) {
		int pu = findPar(u), pv = findPar(v);
		if (pv == pu) return;
		if (size[pv] < size[pu]) {
			parent[pv] = pu;
			size[pu] += size[pv];
		} else {
			parent[pu] = pv;
			size[pv] += size[pu];
		}
	}
};
