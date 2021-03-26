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
 
template<int n>
struct matrix {
  using TYPE = ll;
  TYPE v[n][n];

  matrix() {
    memset(v, 0, sizeof(v));
  }

  matrix<n> mul(matrix &b) {
    matrix<n> res;
	static const ll msq = mod * mod;
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
          res.v[i][j] += v[i][k] * b.v[k][j];
		  if (res.v[i][j] >= msq) res.v[i][j] -= msq;
        }
      }
    }
	for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        res.v[i][j] %= mod;
      }
    }
    return res;
  }

  matrix<n> pow(matrix<n> &a, long long x) {
    matrix<n> res;
    for (int i = 0; i < n; i++) res.v[i][i] = 1;

    while (x) {
      if (x & 1) {
        res = res.mul(a);
      }
      x /= 2;
      a = a.mul(a);
    }
    return res;
  }  
  
  void pr() {
	  cout << "------------\n";
	  for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
		  cout << v[i][j] << " ";
		}
		cout << '\n';
	  }
	  cout << "------------\n";
  }
};

ll n, m, k, q, l, r, x, y, z;
const ll template_array_size = 1e6 + 6884;
ll a[template_array_size];
ll b[template_array_size];
ll c[template_array_size];
string s, t;
ll ans = 0;	

const ll SZ = 95;
map<string, ll> vars;
ll vcnt = 0;
using T = matrix<SZ + 1>;

T rec(ll fac) {
	T cur;
	for (ll i = 0; i < SZ + 1; i++) cur.v[i][i] = 1;
	while (getline(cin, s)) {
		// cout << fac << " | " << s << endl;
		istringstream ss(s);
		ss >> s;
		if (s == "}") break;
		if ('a' <= s[0] && s[0] <= 'z') { // variable
			if (vars.find(s) == vars.end()) {
				vars[s] = vcnt++;
			}
			
			ll p = vars[s];
			
			T upd;
			for (ll i = 0; i < SZ + 1; i++) upd.v[i][i] = 1;
			upd.v[p][p] = 0;
			while (ss >> s) {
				if (s != "(" && s != ")" && s != "=" && s != "+") {
					if (vars.find(s) == vars.end()) { // number
						ll val = stoi(s);
						upd.v[p][SZ] += val;
					} else {
						upd.v[p][vars[s]]++;
					}
				}
			}
			cur = upd.mul(cur);
		} else if (s == "RETURN") {
			ss >> s;
			ll v = 0, p = vars[s];
			cout << cur.v[p][SZ] << '\n';
			exit(0);
		} else {
			ll val = stoi(s);
			T ret = rec(val);
			cur = ret.mul(cur);
		}
	}
		
	cur = cur.pow(cur, fac);
	return cur;
}

void solve(int tc = 0) {
	rec(1);
}

int main() {
	#ifdef galen_colin_local
		auto begin = std::chrono::high_resolution_clock::now();
	#endif
	
	send help
 
	#ifndef galen_colin_local
		usaco("cowbasic");
	#endif
	
	// usaco("cowland");
	
	#ifdef galen_colin_local
		freopen("tc.cpp", "r", stdin);
		// freopen("tc.cpp", "w", stdout);
	#endif
 		
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