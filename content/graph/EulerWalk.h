/**
 * Author: Simon Lindholm
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * Input should be a vector of (dest, global edge index), where
 * for undirected graphs, forward/backward edges have the same index.
 * Returns a list of nodes in the Eulerian path/cycle with src at both start and end, or
 * empty list if no cycle/path exists.
 * for directed graph: indeg = outdeg for every node
 * for undirected graph: every node has even degree
 * Time: O(V + E)
 * Status: stress-tested
 */
#pragma once

void tour(int u) {
	while (!adj[u].empty()) {
		int v = adj[u].back();
		adj[u].pop_back();
		tour(v);
	}
	ans.push_back(u);
}
