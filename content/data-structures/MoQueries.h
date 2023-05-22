/**
 * Author: Sunho
 * Description: Mo's algorithms that can process offline queries if boundary addition/removal to range is defined.
 * Time: Build is $O((N+Q)\sqrt{N})$.
 */
struct mo_query {
  using func = function<void(int)>;
  int n;
  vector<pair<int, int>> lr;
  mo_query(int n) : n(n) {}
  // add query on [l, r]
  void add(int l, int r) { 
    lr.emplace_back(l, r+1);
  }

  void build(const func &add_left, const func &add_right, const func &erase_left, const func &erase_right, const func &out) {
    int q = (int) lr.size();
    int bs = n / min<int>(n, (int)sqrt(q));
    vector<int> ord(q);
    iota(begin(ord), end(ord), 0);
    sort(begin(ord), end(ord), [&](int a, int b) {
      int ablock = lr[a].first / bs, bblock = lr[b].first / bs;
      if(ablock != bblock) return ablock < bblock;
      return (ablock & 1) ? lr[a].second > lr[b].second : lr[a].second < lr[b].second;
    });
    int l = 0, r = 0;
    for(auto idx : ord) {
      while(l > lr[idx].first) add_left(--l);
      while(r < lr[idx].second) add_right(r++);
      while(l < lr[idx].first) erase_left(l++);
      while(r > lr[idx].second) erase_right(--r);
      out(idx);
    }
  }

  void build(const func &add, const func &erase, const func &out) {
    build(add, add, erase, erase, out);
  }
};