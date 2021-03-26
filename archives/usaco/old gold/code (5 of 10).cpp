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
const ll template_array_size = 1e6 + 6884;
ll a[template_array_size];
ll b[template_array_size];
ll c[template_array_size];
string s, t;
ll ans = 0;	

map<int, vector<bool>> ban[20005];
set<int> warn[20005][5];
vector<int> edges[20005];
int par[20005];
const int mod = 1234567;
map<pair<int, int>, int> cache;

int ghash(string s) {
	int t = 1, r = 0;
	for (char c: s) {
		r += t * (c - '0' + 2);
		t *= 50;
	}
	return r;
}

int dfs(int v, string x) {
	int ans = 0;
	
	// cout << "try " << v << " " << x << endl;
	// cout << v << " " << x << " " << warn[v] << endl;
	
	int relevant = -1;
	int chash = 0;
	for (int i = 4; i >= 0; i--) {
		chash *= 50;
		chash += x[i] - '0' + 2;
		if (warn[v][4 - i].size() > 0 && warn[v][4 - i].find(chash) != warn[v][4 - i].end()) {
			relevant = 4 - i;
		}
	}
	
	for (int i = 0; i < 4 - relevant; i++) x[i] = '=';
		
	int xh = ghash(x);
	
	if (cache.find({v, xh}) != cache.end()) return cache[{v, xh}];
	
	string tt = x.substr(1, 4);
	bool check = 0;
	int h = xh / 50;
	vector<bool> banned = ban[v][h];
	
	for (ll i = 0; i < 10; i++) {		
		if (banned.size() == 10 && banned[i]) continue;
		
		if (edges[v].size() == 0) ++ans;
		else {
			ll t = 1;
			string next = tt + (char)(i + '0');
			for (int y: edges[v]) {
				t = (t * dfs(y, next)) % mod;
			}
			ans += t;
			if (ans >= mod) ans -= mod;
		}
	}
		
	return cache[{v, xh}] = ans;
}

void solve(int tc = 0) {
	cin >> n >> m;
	
	for (ll i = 1; i < n; i++) {
		cin >> x;
		edges[x].push_back(i);
		par[i] = x;
	}
	
	for (ll i = 0; i < m; i++) {
		string y;
		cin >> x >> y;
		reverse(y.begin(), y.end());
		
		int h = ghash(y.substr(0, 4));
		if (ban[x].find(h) == ban[x].end()) {
			ban[x][h] = vector<bool>(10, 0);
		}
		ban[x][h][y[4] - '0'] = 1;
		y.pop_back();
		
		for (int j = 0; j < 4; j++) {
			warn[x][y.length() - 1].insert(ghash(y));
			y.pop_back();
			x = par[x];
		}
	}
	
	int r = 1;
	for (ll i = 0; i < n; i++) r = (r * 10) % mod;
	
	cout << (r - dfs(0, "=====") + mod) % mod << '\n';
}

int main() {
	#ifdef galen_colin_local
		auto begin = std::chrono::high_resolution_clock::now();
	#endif
	
	send help
 
	#ifndef galen_colin_local
		usaco("code");
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