namespace fast_dsu {
	const int dsu_MAXN = 100005;
	int dsu_par[dsu_MAXN], dsu_sz[dsu_MAXN];

	void init(int n) {
		for (int i = 0; i < n; i++) {
			dsu_par[i] = i;
		}
		
		memset(dsu_sz, -1, sizeof(dsu_sz));
	}

	int find(int v) {
		// while (v != dsu_par[v]) v = dsu_par[v];
		while ((v = dsu_par[v]) != dsu_par[v]);
		return v;
	}

	bool connected(int v, int u) {
		return find(v) == find(u);
	}

	int merge(int v, int u) {
		// v = find(v);
		// u = find(u);
		
		if (dsu_sz[v] > dsu_sz[u]) {
			int t = v;
			v = u;
			u = t;
		}
		
		dsu_par[u] = v;
		dsu_sz[v] += dsu_sz[u];
	}
}

using namespace fast_dsu;