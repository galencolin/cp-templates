/* from benq's template, fitted to not compile error */
template<class T> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; }

struct MCMF { 
	using F = ll; using C = ll; // flow type, cost type
	struct Edge { int to, rev; F flo, cap; C cost; };
	int N; vector<C> p, dist; vector<pair<int, int>> pre; vector<vector<Edge>> adj;
	void init(int vN) { N = vN;
		p.resize(N), adj.resize(N), dist.resize(N), pre.resize(N); }
	void ae(int u, int v, F cap, C cost) { assert(cap >= 0); 
		adj[u].push_back({v,ll(adj[v].size()),0,cap,cost}); 
		adj[v].push_back({u,ll(adj[u].size())-1,0,0,-cost});
	} // use asserts, don't try smth dumb
	bool path(int s, int t) { // find lowest cost path to send flow through
		const C inf = numeric_limits<C>::max(); dist.assign(N,inf);
		using T = pair<C,int>; priority_queue<T,vector<T>,greater<T>> todo; 
		todo.push({dist[s] = 0,s}); 
		while (ll(todo.size())) { // Dijkstra
			T x = todo.top(); todo.pop(); if (x.f > dist[x.s]) continue;
			for (auto &e: adj[x.s]) { // all weights should be non-negative
				if (e.flo < e.cap && ckmin(dist[e.to],x.f+e.cost+p[x.s]-p[e.to]))
					pre[e.to] = {x.s,e.rev}, todo.push({dist[e.to],e.to});
			}
		} // if costs are doubles, add some EPS so you 
		// don't traverse ~0-weight cycle repeatedly
		return dist[t] != inf; // return flow
	}
	pair<F,C> calc(int s, int t) { assert(s != t);
		for (int _ = 0; _ < N; _++) for (int i = 0; i < N; i++) for (auto &e: adj[i]) // Bellman-Ford
			if (e.cap) ckmin(p[e.to],p[i]+e.cost);
		F totFlow = 0; C totCost = 0;
		while (path(s,t)) { // p -> potentials for Dijkstra
			for (int i = 0; i < N; i++) p[i] += dist[i]; // don't matter for unreachable nodes
			F df = numeric_limits<F>::max();
			for (int x = t; x != s; x = pre[x].f) {
				Edge& e = adj[pre[x].f][adj[x][pre[x].s].rev]; 
				ckmin(df,e.cap-e.flo); }
			totFlow += df; totCost += (p[t]-p[s])*df;
			for (int x = t; x != s; x = pre[x].f) {
				Edge& e = adj[x][pre[x].s]; e.flo -= df;
				adj[pre[x].f][e.rev].flo += df;
			}
		} // get max flow you can send along path
		return {totFlow,totCost};
	}
};