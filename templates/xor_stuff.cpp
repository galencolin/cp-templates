// probably make this not log^2 later lol

struct xor_stuff {
	vector<ll> basis;
	static const int bit_size = 63;
	
	bool insert(ll v) {
		for (ll x: basis) {
			if (v == 0) break;
			if (__builtin_clzll(x) == __builtin_clzll(v)) v ^= x;
		}
		
		if (v > 0) {
			basis.push_back(v);
			sort(basis.begin(), basis.end(), greater<ll>());
			return 1;
		}
		return 0;
	}
	
	bool ask(ll v) {
		for (ll x: basis) {
			if (v == 0) break;
			if (__builtin_clzll(x) == __builtin_clzll(v)) v ^= x;
		}
		
		return !v;
	}
	
	// the values span columns, rows are equations, set value of target to m-th column
	static int gauss (vector < bitset<bit_size> > a, ll m, bitset<bit_size> & ans) {
		int n = a.size();
		
		vector<int> where (m, -1);
		for (int col=0, row=0; col<m && row<n; ++col) {
			for (int i=row; i<n; ++i)
				if (a[i][col]) {
					swap (a[i], a[row]);
					break;
				}
			if (! a[row][col])
				continue;
			where[col] = row;

			for (int i=0; i<n; ++i)
				if (i != row && a[i][col])
					a[i] ^= a[row];
			++row;
		}
		
		for (int i=0; i<m; ++i)
			if (where[i] != -1)
				ans[i] = a[where[i]][m];
		for (int i=0; i<n; ++i) {
			int sum = 0;
			for (int j=0; j<m; ++j)
				sum ^= (ans[j] & a[i][j]);
			if (sum != a[i][m])
				return 0;
		}

		for (int i=0; i<m; ++i)
			if (where[i] == -1)
				return 2;
		return 1;
	}
};