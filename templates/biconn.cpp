bool on[1505][1505];
map<int, int> comp[1505][1505];

const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, -1, 0, 1};

bool valid(int r, int c) {
  return r >= 0 && r < n && c >= 0 && c < m;
}

int _time = 0;

int disc[2250005];
int lvertex[2250005];
int par[2250005];

int cnum = 0;
vector<pii> elist;

void bcc(int v) {
  disc[v] = lvertex[v] = ++_time;
  int cr = v / m, cc = v % m;
  if (!on[cr][cc]) return;

  int child = 0;

  bool f = 0;

  f0r(i, 4) {
    int nr = cr + dr[i], nc = cc + dc[i];

    if (!valid(nr, nc) || !on[nr][nc]) continue;

    int id = nr * m + nc;

    if (disc[id] == -1) {
      child++;
      par[id] = v;

      elist.pb(mp(v, id));
      bcc(id);

      lvertex[v] = min(lvertex[v], lvertex[id]);

      if ((par[v] == -1 && child > 1) || (par[v] != -1 && lvertex[id] >= disc[v])) {
        ++cnum;
        while (elist.back().f != v || elist.back().s != id) {
          int v1 = elist.back().f, v2 = elist.back().s;
          comp[v1 / m][v1 % m][v2] = cnum;
          comp[v2 / m][v2 % m][v1] = cnum;
          elist.pop_back();
        }
        int v1 = elist.back().f, v2 = elist.back().s;
        comp[v1 / m][v1 % m][v2] = cnum;
        comp[v2 / m][v2 % m][v1] = cnum;
        elist.pop_back();
      }
    } else if (id != par[v]) {
      lvertex[v] = min(lvertex[v], disc[id]); 
      if (disc[id] < disc[v]) { 
        elist.pb(mp(v, id)); 
      } 
    }
  }
}

int main() {
  io;
  // freopen("case", "r", stdin);
  // freopen("test.txt", "r", stdin);
  // freopen("case", "w", stdout);

  usaco("pushabox");
  
  cin >> n >> m >> Q;
  f0r(i, n) {
    cin >> s;
    f0r(j, m) {
      on[i][j] = (s[j] != '#');
    }
  }

  // find components
  f0r(i, n*m) {
    disc[i] = -1;
    lvertex[i] = -1;
    par[i] = -1;
  }

  f0r(i, n*m) {
    if (on[i / m][i % m] && disc[i] == -1) bcc(i);

    if (elist.size()) ++cnum;
    while (elist.size()) {
      int v1 = elist.back().f, v2 = elist.back().s;
      comp[v1 / m][v1 % m][v2] = cnum;
      comp[v2 / m][v2 % m][v1] = cnum;
      elist.pop_back();
    }
  }

}
