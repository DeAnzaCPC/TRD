/**
 * Author: Sunho
 * Description: Find max flow of graph. If unit flow is used time comlexity is $O(E\sqrt{V})$
 * Time: O(V^2E) 
 */

struct dinic {
  const int INF = 1e9;
  int n;
  struct dinic_edge {
    int to, cap;
    dinic_edge(int to, int cap) : to(to), cap(cap) {}
  };
  vector<dinic_edge> e;
  vector<vector<int>> g;
  vector<int> cur, h;
  dinic(int n) : n(n), g(n) {}
  bool bfs(int s, int t) {
    h.assign(n, -1);
    queue<int> q;
    h[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i : g[u]) {
        int v = e[i].to;
        int c = e[i].cap;
        if (c > 0 && h[v] == -1) {
          h[v] = h[u] + 1;
          if (v == t)
            return true;
          q.push(v);
        }
      }
    }
    return false;
  }
  int dfs(int u, int t, int f) {
    if (u == t)
      return f;
    int r = f;
    for (; cur[u] < g[u].size(); cur[u]++) {
      int j = g[u][cur[u]];
      int v = e[j].to;
      int c = e[j].cap;
      if (c > 0 && h[v] == h[u] + 1) {
        int a = dfs(v, t, min(r, c));
        e[j].cap -= a;
        e[j ^ 1].cap += a;
        r -= a;
        if (r == 0)
          return f;
      }
    }
    return f - r;
  }
  void add_edge(int u, int v, int c) {
    g[u].push_back(e.size());
    e.push_back({v, c});
    g[v].push_back(e.size());
    e.push_back({u, 0});
  }
  int max_flow(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) {
      cur.assign(n, 0);
      ans += dfs(s, t, INF);
    }
    return ans;
  }
};