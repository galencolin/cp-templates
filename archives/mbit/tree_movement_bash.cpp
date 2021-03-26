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
// const ll mod = 1000000007;
// const ll mod = 998244353;
// ll mod;



ll n, m, k, q, l, r, x, y, z;
const ll template_array_size = 1e6 + 8432;
ll a[template_array_size];
ll b[template_array_size];
ll c[template_array_size];
string s, t;
ll ans = 0;	

vector<ll> ch[100005];
lld v[100005];
ll dep[100005];

lld iter() {
	lld vv[n] = {0};
	for (ll i = 0; i < n; i++) {
		lld s = ch[i].size();
		for (ll j: ch[i]) vv[j] += v[i] / s;
	}
	lld sum = 0;
	for (ll i = 0; i < n; i++) sum += dep[i] * abs(v[i] - vv[i]);
	for (ll i = 0; i < n; i++) v[i] = vv[i];
	return sum;
}

ll getr(ll l, ll r) {
	return rng() % (r - l + 1) + l;
}

void dfs(ll v, ll d) {
	dep[v] = d;
	for (ll x: ch[v]) {
		if (x) dfs(x, d + 1);
	}
}

void solve(int tc = 0) {
	cout.precision(42);
	
	// n = 10000;
	// for (ll i = 1; i < n; i++) {
		// ch[getr(i / 10, i - 1)].push_back(i);
	// }
	// for (ll i = 0; i < n; i++) {
		// if (ch[i].size() == 0) {
			// ch[i].push_back(0);
		// }
	// }
	// dfs(0, 0);
	// cout << dep[n - 1] << '\n';

	n = 5;
	ch[0].push_back(1);
	ch[1].push_back(0);
	ch[0].push_back(2);
	ch[2].push_back(3);
	ch[3].push_back(4);
	ch[4].push_back(0);
		
	memset(v, 0, sizeof(v));
	v[0] = 1;
	ll cnt = 0;
	while (1) {
		for (ll i = 0; i < 500; i++) {
			lld d = iter();
			cout << cnt++ << " |";
			cout << " " << d << " " << seed << endl;
			cout.precision(4);
			for (ll j = 0; j < n; j++) cout << " " << v[j];
			cout.precision(50);
			// cout << endl;
		}
		cin >> s;
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
		// usaco("dining");
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