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
 
ll kk[10] = {
  89, 
  101, 
  189,
  94,
  621,
  (ll)rng() % 1000 + 1051,
  (ll)rng() % 2000 + 2761,
  (ll)rng() % 4000 + 4441,
  27,
  (ll)rng() % 16000 + 18883
};

ll primes[10] = {
  533000401,
  735632791,
  776531419,
  797003413,
  817504243,
  920419813,
  961748941, 
  982451653,
  1000000007,
  1000000009
};

struct string_hash {
  int len;
  ll mod, poly, inv;
  vector<ll> prefix;
  vector<ll> invs;
  
  void init(int n, string s, ll k = 89, ll m = 1000000007) {
    mod = m;
    poly = k;
    prefix = vector<ll>(n);
    invs = vector<ll>(n);

    invs[0] = 1;
    inv = minv(k);
    for (int i = 1; i < n; i++) {
      invs[i] = (invs[i - 1] * inv) % mod;
    }

    ll x = 1;
    prefix[0] = (s[0] - 'a' + 1);
    for (int i = 1; i < n; i++) {
      x = (x * k) % mod;
      prefix[i] = (prefix[i - 1] + x * (s[i] - 'a' + 1)) % mod;
    }

    len = n;
  }

  void extend(string next) {
    int x = next.length();
    for (int i = 0; i < x; i++) {
      invs.push_back((invs[i + len - 1] * inv) % mod);
    }

    ll p = mpow(poly, len - 1);
    for (int i = 0; i < x; i++) {
      p = (p * poly) % mod;
      prefix.push_back((prefix[i + len - 1] + p * (next[i] - 'a' + 1)) % mod);
    }
	
    len += x;
  }
  
  void kill(int sz) {
	  for (int i = 0; i < sz; i++) {
		  invs.pop_back();
		  prefix.pop_back();
	  }
	  
	  len -= sz;
  }

  ll get_hash(int left, int right) {
    if (left == 0) return prefix[right];
    return ((prefix[right] - prefix[left - 1] + mod) * invs[left]) % mod;
  }

  ll mpow(ll base, ll exp) {
    ll res = 1;
    while (exp) {
      if (exp % 2 == 1) {
          res = (res * base) % mod;
      }
      exp >>= 1;
      base = (base * base) % mod;
    }
    return res;
  }
  ll minv(ll base) {
    return mpow(base, mod - 2);
  }
};

template<int K>
struct multihash {
  string_hash sh[K];

  void init(int n, string s) {
    for (int i = 0; i < K; i++) {
      sh[i].init(n, s, kk[9 - i], primes[9 - i]);
    }
  }
  
  void extend(char c) {
	  string s = string(1, c);
	  for (int i = 0; i < K; i++) {
		sh[i].extend(s);
	  }
  }
  
  void kill(int x) {
	  for (int i = 0; i < K; i++) {
		sh[i].kill(x);
	  }
  }

  vector<ll> get_hash(int l, int r) {
    vector<ll> ret(K);
    for (int i = 0; i < K; i++) {
      ret[i] = sh[i].get_hash(l, r);
    }
    return ret;
  }

  bool compare(vector<ll> a, vector<ll> b) {
    for (int i = 0; i < K; i++) {
      if (a[i] != b[i]) return 0;
    }
    return 1;
  }
};

ll n, m, k, q, l, r, x, y, z;
const ll template_array_size = 1e6 + 6884;
ll a[template_array_size];
ll b[template_array_size];
ll c[template_array_size];
string s, t;
ll ans = 0;	

struct node {
	node* nxt[26];
	bool end;
	
	node() {
		for (ll i = 0; i < 26; i++) nxt[i] = nullptr;
		end = 0;
	}
	
	node* next(int v) {
		if (!nxt[v]) nxt[v] = new node;
		return nxt[v];
	}
} *root;

void ins(string s) {
	node* targ = root;
	
	for (ll i = 0; i < s.length(); i++) {
		targ = targ->next(s[i] - 'a');
	}
	targ->end = 1;
}

int ask(string s) {
	node* targ = root;
	
	int ct = 0;
	for (char c: s) {
		if (!targ->nxt[c - 'a']) return -1;
		targ = targ->nxt[c - 'a'];
		++ct;
		if (targ->end) return ct;
	}
	
	return -1;
}

const ll C = 1500;
const ll K = 2;
multihash<K> cur;
vector<ll> lengths;
vector<vector<ll>> big_hashes;

void solve(int tc = 0) {
	cin >> s;
	m = s.length();
	
	root = new node;
	
	cin >> n;
	for (ll i = 0; i < n; i++) {
		cin >> t;
		if (t.length() <= C) {
			reverse(t.begin(), t.end());
			ins(t);
		} else {
			multihash<K> h;
			h.init(t.length(), t);
			big_hashes.push_back(h.get_hash(0, t.length() - 1));
			lengths.push_back(t.length());
		}
	}
			
	cur.init(1, "|");
	string curs = "|";
	
	for (ll i = 0; i < m; i++) {
		cur.extend(s[i]);
		curs.push_back(s[i]);
				
		ll len = min(C, (ll)curs.length() - 1);
		
		int targ = -1;
		string r = curs.substr(curs.length() - len, len);
		reverse(r.begin(), r.end());
		ll v = ask(r);
		
		if (v != -1) targ = v;
		else {
			for (ll j = 0; j < big_hashes.size(); j++) {
				if (curs.length() > lengths[j]) { // > because of filler character
					vector<ll> h1 = cur.get_hash(curs.length() - lengths[j], curs.length() - 1);
					if (cur.compare(h1, big_hashes[j])) {
						targ = lengths[j];
						break;
					}
				}
			}
		}
				
		if (targ != -1) {
			for (ll i = 0; i < targ; i++) curs.pop_back();
			cur.kill(targ);
		}
	}
	
	cout << curs.substr(1, curs.length() - 1) << '\n';
}

int main() {
	#ifdef galen_colin_local
		auto begin = std::chrono::high_resolution_clock::now();
	#endif
	
	send help
 
	#ifndef galen_colin_local
		usaco("censor");
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