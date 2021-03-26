#include <bits/stdc++.h>
using namespace std;

/* 
find my code templates at https://github.com/galencolin/cp-templates
also maybe subscribe please thanks 
*/
 
#define send {ios_base::sync_with_stdio(false);}
#define help {cin.tie(NULL);}
#define f first
#define s second
#define getunique(v) {sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());}
typedef long long ll;
typedef long double lld;
typedef unsigned long long ull;
 
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v);
template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "(" << p.f << ", " << p.s << ")"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
	cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}
template<typename A, typename B> istream& operator>>(istream& cin, pair<A, B> &p) {
	cin >> p.first;
	return cin >> p.second;
}
 
// mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng(61378913);
/* usage - just do rng() */
 
void usaco(string filename) {
  // #pragma message("be careful, freopen may be wrong")
	freopen((filename + ".in").c_str(), "r", stdin);
	freopen((filename + ".out").c_str(), "w", stdout);
}
 
// #include <atcoder/all>
// using namespace atcoder;
 
const lld pi = 3.14159265358979323846;
const ll mod = 1000000007;
// const ll mod = 998244353;
// ll mod;



ll n, m, k, q, l, r, x, y, z;
const ll template_array_size = 1e6 + 8432;
ll a[template_array_size];
ll b[template_array_size];
ll c[template_array_size];
string s, t;
ll ans = 0;	

ll dp[305][305];

void solve(int tc = 0) {
	cin >> n;
	
	for (ll i = 0; i < n; i++) cin >> a[i];
	
	for (ll i = n - 1; i >= 0; i--) {
		dp[i][i] = 1;
		for (ll j = i + 1; j < n; j++) {
			ll cnt = 1, pt = -1, last = -1;
			dp[i][j] = (a[i] != a[j]) + min(dp[i + 1][j], dp[i][j - 1]);
			for (ll k = i + 1; k <= j; k++) {
				ll rest = 0;
				if (k < j) rest = dp[k + 1][j];
				if (a[k] == a[i]) {
					if (pt != -1) {
						cnt += dp[pt][k - 1];
						pt = -1;
					}
					if (last == -1) last = k;
					dp[i][j] = min(dp[i][j], cnt + rest);
				} else {
					if (pt == -1) pt = k;
					last = -1;
					dp[i][j] = min(dp[i][j], cnt + rest + dp[pt][k]);
				}
				if (last != -1 && i + 1 <= last - 1) dp[i][j] = min(dp[i][j], 1 + dp[i + 1][last - 1] + rest);
			}
			
			pt = last = -1;
			cnt = 1;
			for (ll k = j - 1; k >= i; k--) {
				ll rest = 0;
				if (k > i) rest = dp[i][k - 1];
				if (a[k] == a[j]) {
					if (pt != -1) {
						cnt += dp[k + 1][pt];
						pt = -1;
					}
					if (last == -1) last = k;
					dp[i][j] = min(dp[i][j], cnt + rest);
				} else {
					if (pt == -1) pt = k;
					last = -1;
					dp[i][j] = min(dp[i][j], cnt + rest + dp[k][pt]);
				}
				if (last != -1 && last + 1 <= j - 1) dp[i][j] = min(dp[i][j], 1 + dp[last + 1][j - 1] + rest);
			}
		}
	}
	
	cout << dp[0][n - 1] << '\n';
}

// two pointers? maybe
// xor tricks (or general bitwise)
// tutorial on my template

int main() {
	#ifdef galen_colin_local
		auto begin = std::chrono::high_resolution_clock::now();
	#endif
	
	send help
 
	#ifndef galen_colin_local
		// usaco("code");
	#endif
	
	// usaco("cowland");
	
	// freopen("tc.cpp", "r", stdin);
	// freopen("tc.cpp", "w", stdout);
 		
	cout << setprecision(12) << fixed;
					
	int tc = 1;
	// cin >> tc;
	for (int t = 0; t < tc; t++) solve(t);
	
	#ifdef galen_colin_local
		auto end = std::chrono::high_resolution_clock::now();
		cerr << setprecision(4) << fixed;
		// cerr << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << " seconds" << endl;
	#endif
} 