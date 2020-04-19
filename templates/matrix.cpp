struct matrix {
  using TYPE = ll;
  int n;
  vector<vector<TYPE>> v;

  void init(int s) {
    n = s;
    v = vector<vector<TYPE> >(n, vector<TYPE>(n, 0));
  }

  matrix mul(matrix &b) {
    matrix res;
    res.init(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          res.v[i][j] = (res.v[i][j] + v[i][k] * b.v[k][j]) % mod;
        }
      }
    }
    return res;
  }

  matrix pow(matrix &a, long long x) {
    matrix res;
    res.init(n);
    for (int i = 0; i < n; i++) res.v[i][i] = 1;

    while (x) {
      if (x & 1) {
        res = res.mul(a);
      }
      x /= 2;
      a = a.mul(a);
    }
    return res;
  }  
  #pragma message("be careful with mod in matrix")
} base;
