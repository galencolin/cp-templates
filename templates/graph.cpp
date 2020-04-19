struct graph {
  int n;
  vector<bool> vis;
  vector<vector<int> > edges;
  
  void init(int size) {
    n = size;
    vis = vector<bool>(n);
    edges = vector<vector<int> >(n);
  }

  void readGraph(int numEdges, bool isTheGraphUndirected) {
    f0r(i, numEdges) {
      int u, v; cin >> u >> v;
      --u; --v;
      edges[u].pb(v);
      if (isTheGraphUndirected) edges[v].pb(u);
    }
  }

  void bfs(int sourceVertex) {
    fill(vis.begin(), vis.end(), false);

    queue<int> q; 
    q.push(sourceVertex);
    while (!q.empty()) {
      int focusedVertex = q.front();
      q.pop(); 
      if (vis[focusedVertex]) continue; 
      vis[focusedVertex] = 1; 
      
      for (int i: edges[focusedVertex]) {
        if (vis[i]) continue; 
        q.push(i); 
      }
    }
  }
};