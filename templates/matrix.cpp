/* note: additional optimization - first take everything modulo mod^2, using if (x >= mod^2) x -= mod^2, then take everything modulo mod at the end */
template<int n>
struct matrix {
  using TYPE = ll;
  TYPE v[n][n];

  matrix() {
    memset(v, 0, sizeof(v));
  }

  // matrix<n> mul(matrix &b) {
    // matrix<n> res;
    // for (int i = 0; i < n; i++) {
      // for (int k = 0; k < n; k++) {
        // for (int j = 0; j < n; j++) {
          // res.v[i][j] = (res.v[i][j] + v[i][k] * b.v[k][j]) % mod;
        // }
      // }
    // }
    // return res;
  // }
  
  matrix<n> mul(matrix &b) {
    matrix<n> res;
	static const ll msq = mod * mod;
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
          res.v[i][j] += v[i][k] * b.v[k][j];
		  res.v[i][j] = (res.v[i][j] >= msq ? res.v[i][j] - msq : res.v[i][j]);
        }
      }
    }
	for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        res.v[i][j] %= mod;
      }
    }
    return res;
  }

  matrix<n> pow(matrix<n> &a, long long x) {
    matrix<n> res;
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
  
  void pr() {
	  cout << "------------\n";
	  for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
		  cout << v[i][j] << " ";
		}
		cout << '\n';
	  }
	  cout << "------------\n";
  }
  
  #pragma message("be careful with mod in matrix")
};