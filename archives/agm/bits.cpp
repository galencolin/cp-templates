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
typedef int ll;
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

const ll sent = 2e9;

pair<ll, ll> val[50000000];
ll pt[50000000][2];
ll cpt = 1;

void ins(int x, int pos, int worth, int cap) {
	// cout << "ins " << bitset<4>(x) << " " << cap << " " << pos << " " << worth << endl;
  
  int targ = 0;
  
  for (int i = 0; i < cap; i++) {
    int v = !!(x & (1 << i));
	
	// cout << bitset<4>(x) << " " << i << " " << targ << endl;
	
	if (pt[targ][v] == -1) {
		val[cpt] = {sent, -sent};
		pt[targ][v] = cpt++;
	}
	targ = pt[targ][v];
    
	if (i >= pos) {
		val[targ].f = min(val[targ].f, worth);
		val[targ].s = max(val[targ].s, worth);
	}
  }
}

pair<ll, ll> ask(int x, int len) {
	// cout << "ask " << bitset<4>(x) << " " << len << endl;
  
  int targ = 0;
  
  for (int i = 0; i < len; i++) {
	  // cout << bitset<4>(x) << " " << i << " " << targ << endl;
    int v = !!(x & (1 << i));
    
	if (pt[targ][v] == -1) {
		return make_pair(sent, -sent);
	}
	targ = pt[targ][v];
  }

  return val[targ];
}

ll n, m, k, q, l, r, x, y, z;
const ll template_array_size = 1e6 + 8432;
ll a[template_array_size];
ll b[template_array_size];
ll c[template_array_size];
string s, t;
ll ans = 0;	

map<pair<ll, ll>, ll> cnt;
const ll max_bits = 30;

void solve(int tc = 0) {
	cin >> n >> m;
	// n = 1e5;
	// m = 5e3;
	
	memset(pt, -1, sizeof(pt));
	
	for (ll i = 0; i < n; i++) cin >> a[i];
	for (ll i = 0; i < m; i++) cin >> b[i];
	
	// for (ll i = 0; i < n; i++) {
		// a[i] = rng() % (1000000000);
	// }
	// for (ll i = 0; i < m; i++) {
		// b[i] = rng() % (2097152);
	// }
	
	s = "";
	for (ll i = 0; i < m; i++) {
		t = "";
		for (ll j = max_bits - 1; j >= 0; j--) {
			if ((b[i] & (1 << j)) || t.length() > 0) {
				c[s.length() + t.length()] = (1 << j);
				t += '0' + !!(b[i] & (1 << j));
			}
		}
		s += t;
	}
		
	// cout << s << endl;
	// for (ll i = 0; i < s.length(); i++) cout << c[i] << " ";
	// cout << '\n';
	
	for (ll i = 0; i < s.length(); i++) {
		ll lv = max(0, i - (max_bits - 1));
		ll r = 1, tot = 0;
		for (ll j = i; j >= lv; j--) {
			tot += r * (s[j] - '0');
			r *= 2;
		}
		// cout << "S " << i << " " << tot << " " << bitset<4>(tot) << endl;
		ll cap = i - lv + 1;
		ins(tot, 0, 0, cap);
		for (ll j = i; j >= lv; j--) {
			ll dif = i - j;
			ins(tot ^ (1 << dif), dif, c[j], cap);
		}
		// if (i % 1000 == 0) cout << cpt << endl;
	}
				
	for (ll i = 0; i < n; i++) {
		ll len = 0;
		for (ll j = 0; j < max_bits; j++) {
			if ((1 << j) > a[i]) break;
			len = j + 1;
		}
		
		pair<ll, ll> x = ask(a[i], len);
		if (x.f == sent) cout << "-1 -1\n";
		else cout << x.f << " " << x.s << '\n';
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