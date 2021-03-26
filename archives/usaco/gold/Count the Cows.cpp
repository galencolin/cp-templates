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

ll dp[50][6][3];
const ll stop = 39;

ll f(ll st, ll mx) {
	if (mx < 0) return 0;
	
	memset(dp, 0, sizeof(dp));
	ll ans = 0;
	
	dp[0][0][1] = 1;
	for (ll pos = 0; pos < stop; pos++) {
		for (ll ov = 0; ov < 6; ov++) {
			for (ll add = 0; add < 3; add++) {
				ll nv = (st % 3 + ov / 3 + add);
				
				if ((nv % 3) % 2 == add % 2) {
					ll diff = nv % 3 - mx % 3;
					ll state = 1;
					if (diff < 0) state = 0;
					if (diff > 0) state = 2;
										
					if (state != 1) {
						dp[pos + 1][nv][state] += dp[pos][ov][0] + dp[pos][ov][1] + dp[pos][ov][2];
					} else {
						for (ll j = 0; j < 3; j++) {
							dp[pos + 1][nv][j] += dp[pos][ov][j];
						}
					}
				}
			}
		}
		
		st /= 3;
		mx /= 3;
	}
	
	for (ll i = 0; i < 3; i++) {
		for (ll j = 0; j < 2; j++) {
			ans += dp[stop][i][j];
		}
	}
			
	return ans;
}

void solve(int tc = 0) {
	cin >> q;
	
	for (ll i = 0; i < q; i++) {
		ll d;
		cin >> d >> x >> y;
		if (x > y) swap(x, y);
		cout << f(y - x, y + d) - f(y - x, y - 1) << '\n';
	}
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