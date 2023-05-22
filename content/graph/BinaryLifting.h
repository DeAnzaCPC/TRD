/**
 * Author: Ralph
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Calculate power of two jumps in a tree,
 * to support fast upward jumps and LCAs.
 * Assumes the root node points to itself.
 * Time: construction $O(N \log N)$, queries $O(\log N)$
 * Status: Tested at Petrozavodsk, also stress-tested via LCA.cpp
 */
#pragma once

vector<int> adj[MAXN];
int parent[MAXN][20], depth[MAXN];

int getParent(int x, int k) {
  for (int j = 0; k >= 1 << j; j++) {
    if (k & (1 << j))
      x = parent[x][j];
  }
  return x;
}

void dfs(int cur) {
  for (int next : adj[cur]) {
    if (next == parent[cur][0])
      continue;
    parent[next][0] = cur;
    depth[next] = depth[cur] + 1;
    dfs(next);
  }
}

int main() {
  int n, q;
  cin >> n >> q;

  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dfs(1);

  for (int i = 1; i <= 18; i++) {
    for (int j = 1; j <= n; j++) {
      parent[j][i] = parent[parent[j][i - 1]][i - 1];
    }
  }

  for (int i = 0; i < q; i++) {
    int a, b;
    cin >> a >> b;

    if (depth[a] > depth[b])
      swap(a, b);

    int res = depth[b] - depth[a];
    b = getParent(b, res);

    if (a == b) {
      cout << res << endl;
      continue;
    }

    for (int j = 18; j >= 0; j--) {
      if (parent[a][j] != parent[b][j]) {
        res += (2 << j);
        a = parent[a][j];
        b = parent[b][j];
      }
    }

    // res is distance between a and b
    cout << res + 2 << endl;
    // parent[a][0] is LCA
    cout << parent[a][0] << endl;
  }
}