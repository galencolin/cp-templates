struct dijkstra {
  int n;
  const ll inf = 4e18;
  vector<ll> dists; /* for a single run */
  vector<int> par;
  vector<bool> vis;
  vector<vector<pair<ll, int> > > edges; /* weight, to */
  
  void init(int s) {
    n = s;
    dists = vector<ll>(n);
	  vis = vector<bool>(n);
    par = vector<int>(n);
    edges = vector<vector<pair<ll, int> > >(n);
  }

  void edge(int a, int b, ll wt) {
    edges[a].push_back(make_pair(wt, b));
    edges[b].push_back(make_pair(wt, a));
  }

  using ptype = pair<ll, int>;
  void run(int src) {
    fill(dists.begin(), dists.end(), inf);
	  fill(vis.begin(), vis.end(), false);
    fill(par.begin(), par.end(), -1);

    priority_queue<ptype, vector<ptype>, greater<ptype>> pq;
    dists[src] = 0;
    pq.push(make_pair(0, src));
    while (!pq.empty()) {
      ptype foc = pq.top();
      pq.pop();
	  
	    if (vis[foc.s]) continue;
	    vis[foc.s] = 1;
	  
      dists[foc.s] = min(dists[foc.s], foc.f);
      for (ptype x: edges[foc.s]) {
        ll d = dists[foc.s] + x.f;
        if (d < dists[x.s]) {
          dists[x.s] = d;
          par[x.s] = foc.s;
          pq.push(make_pair(d, x.s));
        }
      }
    }
  }
};