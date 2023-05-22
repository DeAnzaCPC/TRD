/**
 * Author: Ralph
 * License: CC0
  * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 */
#pragma once

#include "../data-structures/SegmentTree.h"
vector<int> adj[MAXN];
int vals[MAXN];
// pos is position in heavy[i] is heavy child of i
int parent[MAXN], heavy[MAXN], pos[MAXN], depth[MAXN], head[MAXN];
int curPos = 0;

int dfs(int cur) {
  int size = 1, heavySize = 0;
  for (int next : adj[cur]) {
    if (next == parent[cur])
      continue;
    parent[next] = cur;
    int sz = dfs(next);
    if (sz > heavySize) {
      heavySize = sz;
      heavy[cur] = next;
    }
    size += sz;
  }
  return size;
}

void decompose(int cur, int h) {
  head[cur] = h;
  pos[cur] = curPos++;
  if (heavy[cur] != 0) {
    depth[heavy[cur]] = depth[cur];
    decompose(heavy[cur], h);
  }
  for (int next : adj[cur]) {
    if (next == parent[cur] || next == heavy[cur])
      continue;
    depth[next] = depth[cur] + 1;
    decompose(next, next);
  }
}

int main() {
  int n, q;
  cin >> n >> q;

  for (int i = 1; i <= n; i++)
    cin >> vals[i];

  for (int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(1);
  decompose(1, 1);

  ST st(n);
  for (int i = 1; i <= n; i++) {
    st.tree[n + pos[i]] = vals[i];
  }
  st.init();

  for (int i = 0; i < q; i++) {
    int inp, a, b;
    cin >> inp >> a >> b;
    if (inp == 1) {
      st.update(pos[a], b);
    } else {
      int ans = 0;
      while (head[a] != head[b]) {
        if (depth[a] < depth[b])
          swap(a, b);
        ans = max(ans, st.query(pos[head[a]], pos[a] + 1));
        a = parent[head[a]];
      }
      if (pos[a] > pos[b])
        swap(a, b);
      ans = max(ans, st.query(pos[a], pos[b] + 1));
      cout << ans << endl;
    }
  }
}