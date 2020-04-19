struct bit {
  int n;
  vector<ll> a;
 
  void init(int s) {
    a = vector<ll>(s + 1, 0);
    n = s;
  }
 
  void add(int loc, ll x) {
    if (loc <= 0) return;
    while (loc <= n) {
      a[loc] += x;
      loc += loc & (-loc);
    }
  }
 
  ll query(int loc) {
    ll sum = 0;
    while (loc > 0) {
      sum += a[loc];
      loc -= loc & (-loc);
    }
    return sum;
  }
  
  #pragma message("BITs are 1-indexed, be careful")
};