/**
 * Author: Sunho
 * Description: Find minimum of [l,r] in static array. 
 * Time: Build is $O(N \log N)$ and query is O(1).
 */
int ilog2(int x) {
  return 32-__builtin_clz(x)-1;
}
struct sparse_table {
  vector<vector<int>> st;
  sparse_table(const vector<int>& a) : st(1, a) {
    for (int i=0;i<ilog2(a.size());i++){
      st.emplace_back(a.size());
      for (int j=1<<i;j<a.size();j++) {
        st[i+1][j] = min(st[i][j], st[i][j-(1<<i)]);
      }
    }
  }
  // query on [l, r]
  int query(int l, int r) {
    int i = ilog2(r-l+1);
    return min(st[i][l+(1<<i)-1], st[i][r]);
  }
};
