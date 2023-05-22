/**
 * Author: Ralph
 * Description: Segment tree using binary magic.
 * Time: O(\log N)
 */
template <class T>
struct SegTree {
  const T def = 0; // default value
  int n;
  vector<T> tree;
  SegTree() = default;
  SegTree(int n) : n(n), tree(n * 2, def) {}
	T combine(T a, T b) { return a + b; }
  void init() {
    for (int i = n - 1; i > 0; i--)
      tree[i] = combine(tree[i << 1], tree[i << 1 | 1]);
  }
	void update(int k, T x) { 
		k += n, tree[k] = x;
		for (k >>= 1; k; k >>= 1)
			tree[k] = combine(tree[k << 1], tree[k << 1 | 1]);
	}
	// query on [l,r)
  T query(int l, int r) {
		T resl = def, resr = def;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) resl = combine(resl, tree[l++]);
			if (r & 1) resr = combine(tree[--r], resr);
		}
		return combine(resl, resr);
	}
};
using ST = SegTree<long long>;

pair<int, int> interval(ST st, int i) {
	if (i >= st.n)
		return {i - st.n, i - st.n + 1};
	pair<int, int> l = interval(st, i * 2);
	pair<int, int> r = interval(st, i * 2 + 1);
	if (l.second != r.first)
		return {-1, -1};
	return {l.first, r.second};
}

void debug(ST st) {
	for (int i = 1; i < 2 * st.n; i++) {
		auto res = interval(st, i);
		cout << i << ": [" << res.first << ", " << res.second << ") " << st.tree[i] << endl;
	}
}
