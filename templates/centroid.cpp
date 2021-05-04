struct centroid {
  vector<vector<int> > edges;
  vector<bool> vis;
  vector<int> par;
  vector<int> sz;
  int n;

  void init(int s) {
    n = s;
    edges = vector<vector<int> >(n, vector<int>());
    vis = vector<bool>(n, 0);
    par = vector<int>(n);
    sz = vector<int>(n);
  }

  void edge(int a, int b) {
    edges[a].push_back(b);
    edges[b].push_back(a);
  }

  int find_size(int v, int p = -1) {
    if (vis[v]) return 0;
    sz[v] = 1;

    for (int x: edges[v]) {
      if (x != p) {
        sz[v] += find_size(x, v);
      }
    }

    return sz[v];
  }

  int find_centroid(int v, int p, int n) {
    for (int x: edges[v]) {
      if (x != p) {
        if (!vis[x] && sz[x] > n / 2) {
          return find_centroid(x, v, n);
        }
      }
    }

    return v;
  }

  void init_centroid(int v = 0, int p = -1) {
    find_size(v);

    int c = find_centroid(v, -1, sz[v]);
    vis[c] = true;
    par[c] = p;

    for (int x: edges[c]) {
      if (!vis[x]) {
        init_centroid(x, c);
      }
    }
  }
};