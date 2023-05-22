/**
 * Author: Sunho
 * Description: Finds strongly connected components in a
 * directed graph.
 */

struct sc_components {
  int n;
  vector<vector<int>> adj, adj_inv;
  vector<vector<int>> comps;
  vector<int> comp_ids;
  int num_comp = 0;
  sc_components(int n) : n(n), adj(n), adj_inv(n) {}

  // add edge
  void add(int u, int v) {
    adj[u].push_back(v);
    adj_inv[v].push_back(u);
  }

  // find strongly connected components of graph
  void run() {
    vector<bool> vis(n);
    vector<int> order;
    auto topo_dfs = [&](auto self, int u) -> void {
      vis[u] = true;
      for (int v : adj[u]) if (!vis[v]) self(self, v);
      order.push_back(u);
    };
    for (int i=0;i<n;i++) if(!vis[i]) topo_dfs(topo_dfs, i);
    reverse(begin(order), end(order));
    comp_ids.assign(n, 0);
    vis.assign(n, false);
    auto comp_dfs = [&](auto self, int u) -> void {
      vis[u] = true;
      comp_ids[u] = num_comp;
      comps.back().push_back(u);
      for (int v : adj_inv[u]) if (!vis[v]) self(self, v);
    };
    for (int i : order)
      if (!vis[i]) {
        comps.push_back({});
        comp_dfs(comp_dfs, i);
        num_comp++;
      }
  }
};