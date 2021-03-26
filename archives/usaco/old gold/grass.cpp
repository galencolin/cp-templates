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
// const ll mod = 1000000007;
// const ll mod = 998244353;
// ll mod;
 
struct scc {
  vector<vector<ll> > edges, redges;
  vector<bool> used;
  vector<ll> order, component;
  int n;

  void init(int _n) {
    n = _n;
    edges = vector<vector<ll> >(n);
    redges = vector<vector<ll> >(n);
    order.clear();
    component.clear();
  }

  void edge(int u, int v) {
    edges[u].push_back(v);
    redges[v].push_back(u);
  }

  void dfs1(int v) {
    used[v] = true;
    for (int i = 0; i < edges[v].size(); i++) {
      if (!used[edges[v][i]]) {
        dfs1(edges[v][i]);
      }
    }
    order.push_back(v);
  }

  void dfs2(int v) {
    used[v] = true;
    component.push_back(v);
    for (int i = 0; i < redges[v].size(); i++) {
      if (!used[redges[v][i]]) {
        dfs2(redges[v][i]);
      }
    }
  }

  vector<vector<ll> > run() {
    vector<vector<ll> > components;
    used.assign(n, false);
    for (int i = 0; i < n; i++) {
      if (!used[i]) {
        dfs1(i);
      }
    }

    used.assign(n, false);
    for (int i = 0; i < n; i++) {
      int v = order[n - 1 - i];
      if (!used[v]) {
        dfs2(v);
        components.push_back(component);
        component.clear();
      }
    }

    return components;
  }
};

ll n, m, k, q, l, r, x, y, z;
const ll template_array_size = 1e6 + 6884;
ll a[template_array_size];
ll b[template_array_size];
ll c[template_array_size];
string s, t;
ll ans = 0;	

scc sc;
set<pair<ll, ll>> eset;
vector<pair<ll, ll>> elist;
vector<ll> edges[100005];
ll id[100005];
bool vis[100005];
bool can[100005];

void iter() {
	queue<ll> q;
	memset(vis, 0, sizeof(vis));
	memset(id, 0, sizeof(id));
	for (ll i = 0; i < n; i++) {
		for (ll j: edges[i]) {
			++id[j];
		}
	}
	
	for (ll i = 0; i < n; i++) {
		if (id[i] == 0) q.push(i);
	}
	
	while (!q.empty()) {
		ll x = q.front();
		q.pop();
		
		if (vis[x]) continue;
		vis[x] = 1;
				
		for (ll y: edges[x]) {
			b[y] = max(b[y], a[y] + b[x]);
			if (!vis[y] && --id[y] == 0) q.push(y);
		}
	}
	
	// for (ll i = 0; i < n; i++) cout << make_pair(a[i], b[i]) << " ";
	// cout << '\n';
}
		

void solve(int tc = 0) {
	cin >> n >> m;
	
	sc.init(n);
	
	for (ll i = 0; i < m; i++) {
		cin >> x >> y;
		sc.edge(--x, --y);
		elist.push_back(make_pair(x, y));
	}
	
	vector<vector<ll>> comp = sc.run();
	
	for (ll i = 0; i < comp.size(); i++) {
		for (ll x: comp[i]) a[x] = i;
	}
	
	// for (ll i = 0; i < n; i++) cout << a[i] << " ";
	// cout << '\n';
	
	ll p0 = a[0];
	
	for (pair<ll, ll> x: elist) {
		if (a[x.f] != a[x.s]) eset.insert(make_pair(a[x.f], a[x.s]));
	}
	
	for (pair<ll, ll> x: eset) {
		edges[x.f].push_back(x.s);
	}
	
	n = comp.size();
	for (ll i = 0; i < n; i++) a[i] = comp[i].size();
	
	for (ll i = 0; i < n; i++) b[i] = -1e9;
	b[p0] = 0;
	
	iter();
	
	for (ll i = 0; i < n; i++) {
		c[i] = b[i];
		for (ll j: edges[i]) c[i] = max(c[i], a[i] + b[j]);
	}
	
	// for (ll i = 0; i < n; i++) cout << make_pair(a[i], c[i]) << " ";
	// cout << '\n';
	
	for (ll i = 0; i < n; i++) b[i] = c[i];
	
	iter();
	
	// for (pair<ll, ll> x: eset) cout << x << '\n';
	cout << max(a[p0], b[p0]) << '\n';
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