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
 
mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
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
const ll mod = 1000000007;
// const ll mod = 998244353;
// ll mod;
 
/* union by size */
struct dsu {
  int n;
  vector<int> sizes, marks;
  vector<vector<int> > graph;

  void init(int rn) {
    n = rn;
    sizes = vector<int>(n);
    fill(sizes.begin(), sizes.end(), 1);
    marks = vector<int>(n);
    for (int i = 0; i < n; i++) marks[i] = i;
    graph = vector<vector<int> >(n);
  }

  void mark(int m, int node) {
    if (marks[node] == m) return;

    marks[node] = m;

    for (int i: graph[node]) mark(m, i);
  }

  bool merge(int a, int b) {
    if (marks[a] == marks[b]) return 0;
    graph[a].push_back(b);
    graph[b].push_back(a);

    if (sizes[marks[a]] > sizes[marks[b]]) swap(a, b);

    sizes[marks[b]] += sizes[marks[a]];
    sizes[marks[a]] = 0;
    mark(marks[b], a);
	return 1;
  }

  int find(int n) { return marks[n]; }
};

ll n, m, k, q, l, r, x, y, z;
const ll template_array_size = 1e6 + 6884;
ll a[template_array_size];
ll b[template_array_size];
ll c[template_array_size];
string s, t;
ll ans = 0;	

vector<pair<ll, ll>> edges[200005];
set<pair<ll, ll>> st;
// const ll C = 0;
// const ll S = 50;
const ll C = 25000;
const ll S = 200005 / C + 5;
ll rev[200005];
bool adjb[S][200005];
map<ll, ll> adj[S];
map<ll, set<pair<ll, ll>>> byc[S];
set<pair<ll, ll>> glob[S];
dsu d;

vector<pair<pair<ll, ll>, ll>> elist;
bool comp(pair<pair<ll, ll>, ll> a, pair<pair<ll, ll>, ll> b) {
	return a.s < b.s;
}

inline ll val(ll a, ll b) {
	return min(a, b) * n + max(a, b);
}

void solve(int tc = 0) {
	cin >> n >> m >> k >> q;
	
	for (ll i = 0; i < m; i++) {
		cin >> x >> y >> z;
		--x; --y;
		elist.push_back(make_pair(make_pair(x, y), z));
	}
	
	d.init(n);
	sort(elist.begin(), elist.end(), comp);
	
	for (pair<pair<ll, ll>, ll> x: elist) {
		ll a = x.f.f, b = x.f.s, c = x.s;
		
		if (d.merge(a, b)) {
			edges[a].push_back(make_pair(b, c));
			edges[b].push_back(make_pair(a, c));
		}
	}
	
	for (ll i = 0; i < n; i++) cin >> a[i];
	
	vector<ll> op;
	for (ll i = 0; i < n; i++) {
		if (edges[i].size() > C) {
			ll p = op.size();
			rev[i] = p;
			op.push_back(i);
			for (pair<ll, ll> x: edges[i]) {
				byc[p][a[x.f]].insert(make_pair(x.s, x.f));
			}
			for (pair<ll, set<pair<ll, ll>>> x: byc[p]) {
				glob[p].insert(make_pair(x.s.begin()->f, x.f));
			}
		} else {
			for (pair<ll, ll> x: edges[i]) {
				if (edges[x.f].size() <= C && a[x.f] != a[i]) {
					st.insert(make_pair(x.s, val(i, x.f)));
				}
			}
		}
	}
	
	memset(adjb, 0, sizeof(adjb));
	for (ll i = 0; i < op.size(); i++) {
		for (pair<ll, ll> x: edges[op[i]]) {
			adj[i][x.f] = x.s;
			adjb[i][x.f] = 1;
		}
	}
	
	for (ll i = 0; i < q; i++) {
		ll u, v; cin >> u >> v;
		--u;
				
		ll ov = a[u];
		a[u] = v;
		
		if (edges[u].size() <= C && ov != v) {
			for (pair<ll, ll> x: edges[u]) {
				if (edges[x.f].size() <= C && a[x.f] != ov && a[x.f] == v) {
					st.erase(make_pair(x.s, val(u, x.f)));
				}
			}
	
			for (pair<ll, ll> x: edges[u]) {
				if (edges[x.f].size() <= C && a[x.f] == ov && a[x.f] != v) {
					st.insert(make_pair(x.s, val(u, x.f)));
				}
			}
		}
		
		ll ans = 1e9;
		if (st.size()) ans = st.begin()->f;
		
		for (ll x: op) {
			ll y = rev[x];
			if (adjb[y][u]) {
				ll wt = adj[y][u];
				if (ov != v && x != u) {
					// cout << "S " << x << " " << y << " " << u << endl;
					ll osz = byc[y][ov].size();
					ll nsz = byc[y][v].size();
					
					if (osz) glob[y].erase(make_pair(byc[y][ov].begin()->f, ov));
					if (nsz) glob[y].erase(make_pair(byc[y][v].begin()->f, v));
					
					byc[y][ov].erase(make_pair(wt, u));
					--osz;
					byc[y][v].insert(make_pair(wt, u));
					++nsz;
					
					if (osz) glob[y].insert(make_pair(byc[y][ov].begin()->f, ov));
					if (nsz) glob[y].insert(make_pair(byc[y][v].begin()->f, v));
				}
			}
			if (glob[y].size()) {
				auto it = glob[y].begin();
				if (it->s != a[x]) {
					ans = min(ans, it->f);
				} else if (glob[y].size() > 1) {
					++it;
					ans = min(ans, it->f);
				}
			}
			
			// cout << y << " " << x << "---\n";
			// for (pair<ll, ll> z: glob[y]) cout << z << endl;
		}
		
		cout << ans << '\n';
	}
}

int main() {
	#ifdef galen_colin_local
		auto begin = std::chrono::high_resolution_clock::now();
	#endif
	
	send help
 
	#ifndef galen_colin_local
		usaco("grass");
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
		cout << setprecision(4) << fixed;
		// cout << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << " seconds" << endl;
	#endif
} 