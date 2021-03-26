struct bit {
  int n;
  vector<long long> a;
 
  void init(int s) {
    a = vector<long long>(s + 1, 0);
    n = s;
  }
 
  void add(int loc, long long x) {
    if (loc <= 0) return;
    while (loc <= n) {
      a[loc] += x;
      loc += loc & (-loc);
    }
  }
 
  long long query(int loc) {
    long long sum = 0;
    while (loc > 0) {
      sum += a[loc];
      loc -= loc & (-loc);
    }
    return sum;
  }
};

