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

ll seed = std::chrono::steady_clock::now().time_since_epoch().count();
mt19937_64 rng(seed);
// mt19937_64 rng(61378913);
/* usage - just do rng() */
 
void usaco(string filename) {
  // #pragma message("be careful, freopen may be wrong")
	freopen((filename + ".in").c_str(), "r", stdin);
	freopen((filename + ".out").c_str(), "w", stdout);
}
 
// #include <atcoder/all>
// using namespace atcoder;
 
const lld pi = 3.14159265358979323846;
const ll mod = 100000000007LL;
// const ll mod = 998244353;
// ll mod;



ll n, m, k, q, l, r, x, y, z;
const ll template_array_size = 1e6 + 9097;
ll a[template_array_size];
ll b[template_array_size];
ll c[template_array_size];
string s, t;
ll ans = 0;	

pair<ll, ll> p[100005];
ll nxt[100005];
const ll bits = 8;
const ll mx = (1 << bits);
const ll base = 1000006;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

void solve(int tc = 0) {
	cin >> n >> k;
	
	for (ll i = 0; i < n; i++) {
		cin >> p[i];
		--p[i].s;
	}
	sort(p, p + n);
	
	ll ctime = 1;
	
	ans = -1;
	for (ll i = mx - 1; i >= 0; i--) {
		ll ct = __builtin_popcount(i);
		if (ct < k) continue;
		
		ll cnt[bits] = {0};
		
		vector<ll> at;
		for (ll j = 0; j < bits; j++) {
			if (i & (1 << j)) at.push_back(j);
		}
		
		ll val[bits], tval = 0;
		ll r = 1;
		for (ll j = 0; j < bits; j++) {
			val[j] = r;
			if (i & (1 << j)) tval = (tval + r) % mod;
			r = (r * base) % mod;
		}
		
		gp_hash_table<ll, ll> best;
		
		++ctime;
		
		ll tot = 0;
		
		ll prev = 0;
		
		ll pt = n - 1;
		
		for (ll j = n - 1; j >= 0; j--) {
			if (!(i & (1 << p[j].s))) pt = j - 1;
			nxt[j] = pt;
		}
		
		ll last = 0;
		for (ll j = 0; j < n; j++) {
			if (!(i & (1 << p[j].s))) {
				best.clear();
				memset(cnt, 0, sizeof(cnt));
				last = 0;
				tot = 0;
				prev = j + 1;
			} else {
				if (p[nxt[j]].f - p[j].f > ans - 5) {
					auto it = best.find(last);
					if (it == best.end()) best[last] = p[j].f;
				}
				
				tot += (++cnt[p[j].s] == 1);
				last += val[p[j].s];
				last = (last >= mod ? last - mod : last);
				
				if (tot == ct) {
					last -= tval;
					last = (last < 0 ? last + mod : last);
					for (ll k: at) {
						tot -= (--cnt[k] == 0);
					}
				}
				
				if (p[j].f - p[prev].f > ans - 5) {
					auto it = best.find(last);
					if (it != best.end()) ans = max(ans, p[j].f - it->s);
				}
				
				// cout << i << " " << j << " " << h << " " << p[j] << " " << cnt[0] << " " << cnt[1] << " " << cnt[2] << endl;
			}
		}
	}
	
	cout << ans << '\n';
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
		usaco("fairphoto");
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