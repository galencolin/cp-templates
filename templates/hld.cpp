/* HLD author (this code is modified, but basic stuff is based off this): https://codeforces.com/profile/Vladyslav, code at http://ideone.com/Kquery3Kj 
chaining implementation != fun

somehow this is way slower than their implementation

_version 3 */

/* So how do you use this? 
  First find the operation you need to use
    Change the function OP to fit that
    Change the variable SENTINEL to be a default value for OP
  READ in the number of vertices to n

  CALL init_graph(n) to set up vectors

  READ in the edges, for each edge CALL edge(u, v)

  After the tree is set up, CALL init_hld() to set up the edges, paths, numbering, and segment tree stuff

  READ in the initial values of each node (input may vary) into a vector, vals

  CALL init_values(vals) to set up node values

  The graph is now set up!

  For modifications, CALL modify(node, value)

  For queries, CALL path(u, v)
*/
struct hld {
  using num_t = ll;
  int vert, all, cnt = 1;
  vector<int> heavy, size, p, chain, num, csz, top, depth;
  vector<vector<int>> edges;
  vector<num_t> tree, comp;

  /* change this problem by problem */

  const num_t SENTINEL = 0;

  inline num_t OP(num_t x, num_t y) {
    return x ^ y;
  }

  /* end changeable section */

  void init_graph(int nodes) {
    vert = nodes;
    edges = vector<vector<int>>(vert);
    heavy = vector<int>(vert, -1);
    size = vector<int>(vert);
    p = vector<int>(vert);
    chain = vector<int>(vert);
    num = vector<int>(vert);
    csz = vector<int>(vert);
    top = vector<int>(vert);
    depth = vector<int>(vert);
    tree = vector<num_t>(4 * vert);
    comp = vector<num_t>(4 * vert);
  }

  /* edges are 0-indexed */
  void edge(int a, int b) {
    edges[a].push_back(b);
    edges[b].push_back(a);
  }

  void init_hld() {
    dfs(0);
    decomp(0);
  }

  void init_values(const vector<num_t>& vals) {
    /* assume vals.size() = vert */
    for (int i = 0; i < vert; i++) {
      modify(i, vals[i]);
    }
  }  
  /* basic segment tree stuff */
  void upd(int v, int tl, int tr, int pos, int d){
    if (tl == tr){
      tree[v] = d;
      return;
    }
    int tm = (tl + tr) >> 1;
    if (pos <= tm) upd(v + v, tl, tm, pos, d); else
      upd(v + v + 1, tm + 1, tr, pos, d);
    tree[v] = OP(tree[v + v], tree[v + v + 1]);
  }
  
  num_t query(int v, int tl, int tr, int l, int r){
    if (l > tr || r < tl){
      return SENTINEL;
    }
    if (l <= tl && r >= tr){
      return tree[v];
    }
    int tm = (tl + tr) >> 1;
    return OP(query(v + v, tl, tm, l, r), query(v + v + 1, tm + 1, tr, l, r));
  }
  /* end segtree part */
  
  void dfs(int v, int parent = 0){
    p[v] = parent;
    size[v] = 1;
    for (int i = 0; i < edges[v].size(); i++) {
      int to = edges[v][i];
      if (to == parent){
        continue;
      }
      depth[to] = depth[v] + 1;
      dfs(to, v);
      size[v] += size[to];
      if (heavy[v] == -1 || size[to] > size[heavy[v]]){
        heavy[v] = to;
      }
    }
  }
  
  void decomp(int v, int parent = -1){
    chain[v] = cnt - 1;
    num[v] = all++;
    if (!csz[cnt - 1]){
      top[cnt - 1] = v;
    }
    ++csz[cnt - 1];
    if (heavy[v] != -1){
      decomp(heavy[v], v);
    }
    for (int i = 0; i < edges[v].size(); i++) {
      int to = edges[v][i];
      if (to == parent || to == heavy[v]){
        continue;
      }
      ++cnt;
      decomp(to, v);
    }
  }
  
  num_t path(int a, int b){
    num_t res = SENTINEL;
    while (chain[a] != chain[b]){
      if (depth[top[chain[a]]] < depth[top[chain[b]]]) swap(a, b);
      int start = top[chain[a]];
      if (num[a] == num[start] + csz[chain[a]] - 1)
        res = OP(res, comp[chain[a]]);
      else
        res = OP(res, query(1, 0, vert - 1, num[start], num[a]));
      a = p[start];
    }
    if (depth[a] > depth[b]) swap(a, b);
    res = OP(res, query(1, 0, vert - 1, num[a], num[b]));
    return res;
  }
  
  void modify(int edge, int v){
    upd(1, 0, vert - 1, num[edge], v);
    int start = num[top[chain[edge]]];
    int end = start + csz[chain[edge]] - 1;
    comp[chain[edge]] = query(1, 0, vert - 1, start, end);
  }
};