/* cost function must be defined */
int cost(int i, int j) {
  if (i == 0) return pre[j][j] / 2;
  return (pre[j][j] - pre[j][i-1] - pre[i-1][j] + pre[i-1][i-1]) / 2;
}

/* divide and conquer dp */
void div(int k, int il, int ih, int optl, int optr) {
  if (il > ih) return;
  int mid = (il + ih) / 2;
  dp[mid][k] = 1e9;
  int opt = optl;
  for (int i = optl - 1; i <= min(mid, optr + 1); i++) {
    int v = cost(i, mid);
    if (i > 0) v += dp[i - 1][k - 1];
    if (v < dp[mid][k]) {
      dp[mid][k] = v;
      opt = i;
    }
  }

  div(k, il, mid - 1, optl, opt);
  div(k, mid + 1, ih, opt, optr);
}

/* just do it all */
/* remember to initialize first row (dp[0][0..k-1]) */
void dcq() {
	for (int z = 1; z < k; z++) {
		div(j, 0, n-1, 0, n-1);
	}
}

/* sample main function */
/* problem: https://codeforces.com/contest/321/problem/E */
int main() {
  ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> k;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      char c;
      cin >> c;
      grid[i][j] = c - '0';
    }
  }

  f0r(i, n) {
    pre[i][0] = grid[i][0];
    f1r(j, 1, n) pre[i][j] = grid[i][j] + pre[i][j-1];
  }

  f1r(i, 1, n) f0r(j, n) pre[i][j] += pre[i-1][j];

  f0r(i, n) dp[i][0] = cost(0, i);
  

  cout << dp[n-1][k-1] << endl;
}