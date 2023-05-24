/**
 * Author: Sunho
 * Description: 2D Fenwick tree
 * Time: Both operations are $O(\log N)$.
 */

struct fenwick_tree_2d {
  int n, m;
  vector<vector<ll>> bits;
  fenwick_tree_2d(int n, int m) : n(n), m(m), bits(n+1, vector<ll>(m+1)) {}
  void update(int i, int j, int delta) { 
    for (++i; i <= n; i += i&(-i))
      for (int jj=j+1; jj <= m; jj += jj&(-jj))
        bits[i][jj] += delta;
  }
  ll query(int i, int j) {
    ll res = 0;
    for (++i; i > 0; i -= i&(-i))
      for (int jj=j+1; jj > 0; jj -= jj&(-jj))
        res += bits[i][jj];
    return res;
  }
  // Sum of all elements in [i1,i2]x[j1,j2] (sum of elements in box containing (i1,j1) and (i1,j2))
  ll query(int i1, int j1, int i2, int j2) { 
    return query(i2, j2) + query(i1-1, j1-1) - query(i1-1,j2) - query(i2,j1-1); 
  }
};