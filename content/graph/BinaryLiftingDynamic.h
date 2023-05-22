/**
 * Author: Sunho
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Binary lifting with dynamic size;
 */
#pragma once

vector<vector<int>> treeJump(vector<int>& P){
	int d = ceil(log2(P.size()));
	vector<vector<int>> up(d, P);
	for(int i=1;i<d;i++) for(int j=0;j<P.size();j++)
		up[i][j] = up[i-1][up[i-1][j]];
	return up;
}

int jmp(vector<vector<int>>& up, int node, int steps){
	for(int i=0;i<up.size();i++)
		if(steps&(1<<i)) node = up[i][node];
	return node;
}

int lca(vector<vector<int>>& up, vector<int>& depth, int a, int b) {
	if (depth[a] < depth[b]) swap(a, b);
	a = jmp(up, a, depth[a] - depth[b]);
	if (a == b) return a;
	for (int i = up.size()-1;i>=0;i--) {
		int c = up[i][a], d = up[i][b];
		if (c != d) a = c, b = d;
	}
	return up[0][a];
}

