#include <bits/stdc++.h>
using namespace std;
 
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
// const ll mod = 1000000007;
// const ll mod = 998244353;
// ll mod;


 
ll n, m, k, q, l, r, x, y, z;
const ll template_array_size = 1e6 + 8061;
ll a[template_array_size];
ll b[template_array_size];
ll c[template_array_size];
string s, t;
ll ans = 0;	

set<pair<ll, ll>> nxt[100005];
ll cyc[100005];
ll res[100005];
ll vis[100005];
pair<ll, ll> p[200005];
vector<pair<ll, ll>> at[100005];
ll pos[100005];
vector<ll> cv[100005];
ll cnt[100005];
vector<pair<ll, ll>> circ;

void solve(int tc = 0) {
	cin >> n >> k;
	cin >> m;
	
	for (ll i = 0; i < k; i++) {
		cin >> p[i];
		--p[i].f; --p[i].s;
		nxt[p[i].f].insert(make_pair(i, p[i].s));
		nxt[p[i].s].insert(make_pair(i, p[i].f));
	}
	
	memset(cyc, -1, sizeof(cyc));
	memset(vis, -1, sizeof(vis));
	iota(a, a + n, 0);
	
	for (ll i = 0; i < k; i++) {
		swap(a[p[i].f], a[p[i].s]);
	}
	
	for (ll i = 0; i < n; i++) b[a[i]] = i;
	for (ll i = 0; i < n; i++) a[i] = b[i];
	
	for (ll i = 0; i < n; i++) {
		pair<ll, ll> pos = make_pair(0, i);
		at[i].push_back(make_pair(i, 0));
		vis[i] = i;
		while (1) {
			auto nv = nxt[pos.s].lower_bound(make_pair(pos.f, -1));
			if (nv == nxt[pos.s].end()) break;
			else pos = make_pair(nv->f + 1, nv->s);
			
			if (vis[pos.s] != i) at[i].push_back(make_pair(pos.s, pos.f));
			vis[pos.s] = i;
		}
	}
	
	memset(vis, -1, sizeof(vis));
	
	ll ct = 0;
	for (ll i = 0; i < n; i++) {
		if (cyc[i] == -1) {
			ll pv = 0, p = a[i];
			while (p != i) {
				cyc[p] = ct;
				cv[ct].push_back(p);
				pos[p] = pv++;
				p = a[p];
			}
			cyc[i] = ct;
			cv[ct].push_back(i);
			pos[i] = pv++;
									
			++ct;
		}
	}
	
	memset(cnt, 0, sizeof(cnt));
	memset(vis, 0, sizeof(vis));
	
	for (ll i = 0; i < n; i++) {
		if (vis[cyc[i]]) continue;
		vis[cyc[i]] = 1;
		circ.clear();
		
		vector<ll> cva = cv[cyc[i]];
		
		for (ll j = 0; j < cva.size() * 2; j++) {
			for (pair<ll, ll> x: at[cva[j % cva.size()]]) {
				circ.push_back(make_pair(x.f, k * j + x.s));
			}
		}
		
		ll p1 = 0, p2 = 0, r = 0;
		for (ll j = 0; j < cva.size(); j++) {
			ll v = cva[j];
			ll targ = k * j;
			while (p1 < circ.size() && circ[p1].s < targ) {
				if (--cnt[circ[p1++].f] == 0) --r;
			}
			targ = k * j + m;
			while (p2 < circ.size() && circ[p2].s <= targ) {
				if (++cnt[circ[p2++].f] == 1) ++r;
			}
			res[cva[j]] = r;			
		}
		
		for (pair<ll, ll> x: circ) cnt[x.f] = 0;
	}
	
	for (ll i = 0; i < n; i++) cout << res[i] << '\n';
}

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