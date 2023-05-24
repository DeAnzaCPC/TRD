/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest paths from $s$ in a graph that might have negative edge weights.
 * Unreachable nodes get dist = inf; nodes reachable through negative-weight cycles get dist = -inf.
 * Assumes $V^2 \max |w_i| < \tilde{} 2^{63}$.
 * Time: O(VE)
 * Status: Tested on kattis:shortestpath3
 */

vector<ll> dist(n, -inf);
dist[0] = 0;
for (int t=0;t<n;t++){
	for (int i=0;i<m;i++){
		auto [a,b,w] = edges[i];
		if (dist[a] != -inf)
			dist[b] = max(dist[b], dist[a]+w);
	}
}
vector<bool> neg(n,false);
for (int t=0;t<n;t++){
	for (int i=0;i<m;i++){
		auto [a,b,w] = edges[i];
		if (dist[a] != -inf && dist[b] < dist[a]+w) {
			neg[a] = true;
		}
		neg[b] = neg[b] || neg[a];
	}
}