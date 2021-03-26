using implicit_segtree = struct implicit_segtree;
using T = short;
struct implicit_segtree {
  implicit_segtree* child[2];
  T v;
  static const ll implicit_sz = 1.1e18;
  static const T base = 0;
 
  implicit_segtree() {
	v = base;
    child[0] = nullptr;
    child[1] = nullptr;
  }
 
  implicit_segtree* ch(int x) {
    if (!child[x]) child[x] = new implicit_segtree();
    return child[x];
  }
  
  inline T op(T a, T b) {
	  return max(a, b);
  }
 
  void upd(ll loc, T val) {
    upd(loc, val, 0, implicit_sz - 1);
  }
 
  T upd(ll loc, T val, ll l, ll r) {
    if (l > loc || r < loc) return v;
    if (l == r) return v = val;
    ll m = (l + r) / 2;
    T a = base, b = base;
    if (loc <= m) {
      a = ch(0)->upd(loc, val, l, m);
      if (child[1]) b = ch(1)->v;
    } else {
      if (child[0]) a = ch(0)->v;
      b = ch(1)->upd(loc, val, m + 1, r);
    }
    
    return v = op(a, b);
  }
 
  T query(ll ql, ll qr) {
    return query(ql, qr, 0, implicit_sz - 1);
  }
 
  T query(ll ql, ll qr, ll tl, ll tr) {
    if (qr < tl || ql > tr || tl > tr) return base;
    if (ql <= tl && tr <= qr) return v;
    T a = base, b = base;
	ll m = (tl + tr) / 2;
    if (child[0]) a = ch(0)->query(ql, qr, tl, m);
    if (child[1]) b = ch(1)->query(ql, qr, m + 1, tr);
    return op(a, b);
  }
};