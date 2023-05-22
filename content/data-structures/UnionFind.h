/**
 * Author: Ralph
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
#define MAXN 100000

//can also be by rank
int parent[MAXN], sz[MAXN]; 

void make_set(int v) { 
	parent[v] = v;
	sz[v] = 1;
}

int find_set(int v) {
  if (parent[v] == v)
		return v;
  return parent[v] = find_set(parent[v]);
}

void union_set(int a, int b) {
	a = find_set(a);
	b = find_set(b);
  if (sz[a] > sz[b]) {
		swap(a, b);
  }
  parent[a] = b;
  sz[b] += sz[a];
}