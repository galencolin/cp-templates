/* union by size */
struct dsu {
  int n;
  vector<int> sizes, marks, nedges;
  vector<vector<int> > graph;

  void init(int rn) {
    n = rn;
    sizes = vector<int>(n);
    nedges = vector<int>(n);
    fill(sizes.begin(), sizes.end(), 1);
    marks = vector<int>(n);
    for (int i = 0; i < n; i++) marks[i] = i;
    graph = vector<vector<int> >(n);
  }

  void mark(int m, int node) {
    if (marks[node] == m) return;

    marks[node] = m;

    for (int i: graph[node]) mark(m, i);
  }

  void merge(int a, int b) {
    if (marks[a] == marks[b]) {
        nedges[marks[b]] ++;
        return;
    }
    graph[a].push_back(b);
    graph[b].push_back(a);

    if (sizes[marks[a]] > sizes[marks[b]]) swap(a, b);

    sizes[marks[b]] += sizes[marks[a]];
    sizes[marks[a]] = 0;
    nedges[marks[b]] += (nedges[marks[a]] + 1);
    nedges[marks[a]] = 0;
    mark(marks[b], a);
  }

  int find(int n) { return marks[n]; }
};
