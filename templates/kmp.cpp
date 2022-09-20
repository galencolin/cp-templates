vector<int> compute_lps(vector<ll> pat) {
    int n = pat.size();
    vector<int> lps(n);
    lps[0] = 0;
    for (int i = 1; i < n; i++) {
        lps[i] = 0;
        int j = lps[i - 1]; /* trying length j + 1 */
        while (j > 0 && pat[j] != pat[i]) {
            j = lps[j - 1];
        }
        if (pat[j] == pat[i]) {
            lps[i] = j + 1;
        }
    }
    return lps;
}

vector<int> find_matches(vector<ll> text, vector<ll> pat) {
    int n = pat.size(), m = text.size();
    vector<ll> v = pat;
    v.push_back(-1);
    v.insert(v.end(), text.begin(), text.end());
    vector<int> lps = compute_lps(v), ans;
    for (int i = n + 1; i <= n + m; i++) { /* n + 1 is where the text starts */
        if (lps[i] == n) {
            ans.push_back(i - 2 * n); /* i - (n - 1) - (n + 1) */
        }
    }
    return ans;
}
