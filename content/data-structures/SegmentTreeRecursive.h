/**
 * Author: Sunho
 * Description: Recursive segment tree.
 * Time: O(\log N)
 */
const int inf = 1e9;
struct seg_tree {
  typedef int Info;
  int n;
  vector<Info> info;
  const Info def = inf;
  seg_tree(int n) : n(n), info(4*n, def) {}
  Info combine(const Info& a, const Info& b) { return min(a,b); }
  void pull(int v) { info[v] = info[v*2] + info[v*2+1]; }
  void update(int v, int l, int r, int x, const Info& val) {
    if (l == r) {
      info[v] = val;
      return;
    }
    int m = (l + r) / 2;
    if (x <= m) update(v*2, l, m, x,  val);
    else update(v*2+1, m+1, r, x, val); 
    pull(v);
  }
  void update(int x, const Info& val) { update(1, 0, n-1, x, val); }
  // query on [l,r]
  Info query(int v, int l, int r, int x, int y) {
    if (l > y || r < x)
      return def;
    if (l >= x && r <= y)
      return info[v];
    int m = (l + r) / 2;
    pull(v);
    return query(2*v, l, m, x, y) + query(2*v+1, m+1, r, x, y);
  }
  Info query(int l, int r) { return query(1, 0, n-1, l, r); }
};
