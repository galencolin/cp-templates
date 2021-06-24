// I don't get it, but...
// https://cses.fi/problemset/task/2086

#include "bits/stdc++.h"
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
// typedef int ll;
// #pragma warning("int")
 
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

// requires: lines & queries be sorted in order of slope
// https://codeforces.com/blog/entry/63823
// also has a problem with parallel lines i think
struct line {
    long long m, c;
    long long eval(long long x) { return m * x + c; }
    long double intersectX(line l) { return (long double) (c - l.c) / (l.m - m); }
};

struct fast_hull {
	deque<line> dq;
	
	fast_hull() {
		dq = deque<line>();
	}
	
	ll query(ll x) {
		while (dq.size() >= 2 && dq.back().eval(x) >= dq[dq.size() - 2].eval(x))
			dq.pop_back();
		// for (line l: dq) cout << "line " << l.m << " " << l.c << " " << l.eval(x) << endl;
		return dq.back().eval(x);
	}
	
	void insert(ll m, ll c) {
		line x{m, c};
		while (dq.size() >= 2 && x.intersectX(dq[0]) <= dq[0].intersectX(dq[1]))
			dq.pop_front();
		dq.push_front(x);
	}
};
 
ll n, m, q, k, l, r, x, y, z;
const ll template_array_size = 1e6 + 15258;
ll a[template_array_size];
ll b[template_array_size];
ll c[template_array_size];
string s, t;
 
ll dp[3005][3005];
 
// (p(i) - p(j))^2 = p(i)^2 - 2p(i)p(j) + p(j)^2
/* 
	try to think a bit more to simplify if sol is complicated
	also look for edge cases, please
*/
void solve(int tc = 0) {
	cin >> n >> k;
	for (ll i = 0; i < n; i++) cin >> a[i];
	
	memset(dp, 1, sizeof(dp));
	dp[0][0] = 0;
	
	ll p = 0;
	for (ll i = 0; i < n; i++) {
		p += a[i];
		dp[0][i + 1] = p * p;
	}
	
	for (ll i = 1; i < k; i++) {
		ll p = 0;
		fast_hull dh;
		
		for (ll j = i; j <= n; j++) {
			dh.insert(-2 * p, (dp[i - 1][j - 1] + p * p));
			
			p += a[j - 1];
			
			dp[i][j] = p * p + dh.query(p);
			
			// cout << i << " " << j << " " << dp[i][j] << endl;
		}
	}
	
	cout << dp[k - 1][n] << '\n';
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
	// freopen("tc2.cpp", "w", stdout);
		
	cout << setprecision(15) << fixed;
	
	
		
	int tc = 1;
	// cin >> tc;
	for (int t = 0; t < tc; t++) solve(tc);
	
	#ifdef galen_colin_local
		auto end = std::chrono::high_resolution_clock::now();
		cerr << setprecision(4) << fixed;
		cerr << "Execution time: " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << " seconds" << endl;
	#endif
} 