using implicit_segtree = struct implicit_segtree;
struct implicit_segtree {
  ll v, sz;
  implicit_segtree* child[2];
  ll base = 0;
 
  implicit_segtree() {
 
  }
 
  implicit_segtree(ll n) {
    v = base;
    child[0] = nullptr;
    child[1] = nullptr;
    sz = n;
  }
 
  implicit_segtree* ch(int x) {
    if (!child[x]) child[x] = new implicit_segtree(sz);
    return child[x];
  }
  
  inline ll op(ll a, ll b) {
	  return max(a, b);
  }
 
  void upd(ll loc, ll val) {
    upd(loc, val, 0, sz - 1);
  }
 
  ll upd(ll loc, ll val, ll l, ll r) {
    if (l > loc || r < loc) return v;
    if (l == r) return v = val;
    ll m = (l + r) / 2;
    ll a = base, b = base;
    if (loc <= m) {
      a = ch(0)->upd(loc, val, l, m);
      if (child[1]) b = ch(1)->v;
    } else {
      if (child[0]) a = ch(0)->v;
      b = ch(1)->upd(loc, val, m + 1, r);
    }
    
    return v = op(a, b);
  }
 
  ll query(ll ql, ll qr) {
    return query(ql, qr, 0, sz - 1);
  }
 
  ll query(ll ql, ll qr, ll tl, ll tr) {
    if (qr < tl || ql > tr || tl > tr) return base;
    if (ql <= tl && tr <= qr) return v;
    ll a = base, b = base, m = (tl + tr) / 2;
    if (child[0]) a = ch(0)->query(ql, qr, tl, m);
    if (child[1]) b = ch(1)->query(ql, qr, m + 1, tr);
    return op(a, b);
  }
};