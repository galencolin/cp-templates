/* from benq's template, fitted to not compile error */
template<int SZ> struct Dinic {
	#define sz(x) ((int)x.size())
	int N,s,t;
	typedef ll F;
	struct Edge { int to, rev; F flo, cap; };
	vector<Edge> adj[SZ];
	void ae(int u, int v, F cap, F rcap = 0) { 
		assert(min(cap,rcap) >= 0); 
		Edge a{v,sz(adj[v]),0,cap}, b{u,sz(adj[u]),0,rcap};
		adj[u].push_back(a), adj[v].push_back(b); } 
	int lev[SZ]; typename vector<Edge>::iterator cur[SZ]; 
	bool bfs() {
		for (ll i = 0; i < N; i++) lev[i] = -1, cur[i] = begin(adj[i]);
		queue<int> q({s}); lev[s] = 0; 
		while (sz(q)) {
			int u = q.front(); q.pop();
			for(auto e: adj[u]) if (lev[e.to] < 0 && e.flo < e.cap) 
				q.push(e.to), lev[e.to] = lev[u]+1;
		}
		return lev[t] >= 0;
	}
	F dfs(int v, F flo) {
		if (v == t) return flo;
		for (; cur[v] != end(adj[v]); cur[v]++) {
			Edge& e = *cur[v];
			if (lev[e.to]!=lev[v]+1||e.flo==e.cap) continue;
			F df = dfs(e.to,min(flo,e.cap-e.flo));
			if (df) { e.flo += df; adj[e.to][e.rev].flo -= df;
				return df; }
		}
		return 0;
	}
	F maxFlow(int NN, int ss, int tt) {
		N = NN, s = ss, t = tt; assert(s != t);
		F tot = 0; while (bfs()) while (F df = 
			dfs(s,numeric_limits<F>::max())) tot += df;
		return tot;
	}
};