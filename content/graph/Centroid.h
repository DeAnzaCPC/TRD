/**
 * Author: Ralph
 * Description: Find centroid of tree.
 */
int n, sz[MAXN];
vector<int> adj[MAXN];

void dfsSize(int cur, int prev) {
  sz[cur] = 1;
  for (int next : adj[cur]) {
    if (next == prev)
      continue;
    dfsSize(next, cur);
    sz[cur] += sz[next];
  }
}

int getCentroid(int cur, int prev) {
  for (int next : adj[cur]) {
    if (next == prev)
      continue;
    if (sz[next] * 2 > n)
      return getCentroid(next, cur);
  }
  return cur;
}
