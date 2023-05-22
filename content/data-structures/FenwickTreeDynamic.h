/**
 * Author: Sunho
 * Description: Fenwick tree with dynamic size for partial sum.
 * Time: Both operations are $O(\log N)$.
 */
struct fenwick_tree {
  int n;
  vector<ll> bits;
  fenwick_tree(int n) : n(n), bits(n+1) {}
  void update(int v, int delta) { 
    for (++v; v <= n; v += v&(-v)) bits[v] += delta;
  }
  ll query(int r) {
    ll res = 0;
    for (++r; r > 0; r -= r&(-r)) res += bits[r];
    return res;
  }
	// sum of [l, r]
  ll query(int l, int r) { return query(r) - query(l-1); }
};
