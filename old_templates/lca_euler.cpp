/* uses modified segtree and min_t */
/* adapt later for generic rmq */
template <typename num_t> 
struct segtree {
  int n, depth;
  vector<num_t> tree, lazy;

  void init(int s, long long* arr) {
    n = s;
    tree = vector<num_t>(4 * s, 0);
    lazy = vector<num_t>(4 * s, 0);
    init(0, 0, n - 1, arr);
  }

  num_t init(int i, int l, int r, long long* arr) {
    if (l == r) return tree[i] = num_t(arr[l], l);

    int mid = (l + r) / 2;
    num_t a = init(2 * i + 1, l, mid, arr),
          b = init(2 * i + 2, mid + 1, r, arr);
    return tree[i] = a.op(b);
  }

  void update(int l, int r, num_t v) {
    update(0, 0, n - 1, l, r, v);
  }

  num_t update(int i, int tl, int tr, int ql, int qr, num_t v) {
    eval_lazy(i, tl, tr);

    if (ql <= tl && tr <= qr) {
      lazy[i] = lazy[i].val + v.val;
      eval_lazy(i, tl, tr);
      return tree[i];
    }
    if (tl > tr || tr < ql || qr < tl) return tree[i];
    if (tl == tr) return tree[i];

    int mid = (tl + tr) / 2;
    num_t a = update(2 * i + 1, tl, mid, ql, qr, v),
          b = update(2 * i + 2, mid + 1, tr, ql, qr, v);
    return tree[i] = a.op(b);
  }

  num_t query(int l, int r) {
    return query(0, 0, n-1, l, r);
  }

  num_t query(int i, int tl, int tr, int ql, int qr) {
    eval_lazy(i, tl, tr);
    
    if (ql <= tl && tr <= qr) return tree[i];
    if (tl > tr || tr < ql || qr < tl) return num_t::null_v;

    int mid = (tl + tr) / 2;
    num_t a = query(2 * i + 1, tl, mid, ql, qr),
          b = query(2 * i + 2, mid + 1, tr, ql, qr);
    return a.op(b);
  }

  /* varies by implementation */
  /* this one is for range additions */
  void eval_lazy(int i, int l, int r) {
    /* special part */
    tree[i] = tree[i].lazy_op(lazy[i], (r - l + 1));
    if (l != r) {
      lazy[i * 2 + 1] = lazy[i].val + lazy[i * 2 + 1].val;
      lazy[i * 2 + 2] = lazy[i].val + lazy[i * 2 + 2].val;
    }
    /* end special part */

    lazy[i] = num_t();
  }
};

struct min_t {
  long long val;
  int ind;
  static const long long null_v = 9223372036854775807LL;

  min_t(): val(0) {}
  min_t(long long v): val(v) {}
  min_t(long long v, int i): val(v), ind(i) {};

  min_t op(min_t& other) {
    if (other.val == val) 
      return (ind > other.ind) ? other : *this;
    return (val > other.val) ? other : *this;
  }
  
  min_t lazy_op(min_t v, int size) {
    return min_t(val + v.val, ind);
  }
};

struct lca {
  int n, root;
  vector<int> parents, euler, f, depths;
  int* depth_a;
  segtree<min_t> st;
  vector<vector<int> > edges;

  void init(int size, int r) {
    n = size;
    root = r;
    edges = vector<vector<int> >(n);
    parents = vector<int>(n);
    f = vector<int>(n, -1);
  }

  void edge(int a, int b) {
    edges[a].push_back(b);
    edges[b].push_back(a);
  }

  /* when graph is complete */
  void init_lca() {
    set_parents(-1, root);
    euler_tour(root, 0);
    depth_a = new int[2 * n];
    for (int i = 0; i < 2 * n - 1; i++) {
      depth_a[i] = depths[i];
      if (f[euler[i]] == -1) f[euler[i]] = i;
    }
    st.init(2 * n - 1, depth_a);
  }

  void set_parents(int parent, int node) {
    parents[node] = parent;
    for (int i: edges[node]) 
      if (i != parent) set_parents(node, i);
  }

  void euler_tour(int node, int d) {
    euler.push_back(node);
    depths.push_back(d);
    for (int i: edges[node]) 
      if (i != parents[node]) {
        euler_tour(i, d + 1);
        euler.push_back(node);
        depths.push_back(d);
      }
  }

  int q(int a, int b) {
    if (a == b) return a;
    int c = min(f[a], f[b]), d = max(f[a], f[b]);
    return euler[(st.query(c, d)).ind];
  }
};
