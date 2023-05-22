/**
 * Author: Ralph
 * Description: Matrix
 */
#define MOD 1000000007ll

struct Matrix {
	int n, m;
	vector<vector<long long>> vals;

	Matrix(int n, int m) : n(n), m(m), vals(n, vector<long long>(m)) {}

	vector<long long>& operator[](int i) {
		return vals[i];
	}

	Matrix operator*(const Matrix &other) {
		Matrix res(n, other.m);
		for (int k = 0; k < m; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < other.m; j++) {
					res[i][j] += vals[i][k] * other[k][j];
					res[i][j] %= MOD;
				}
			}
		}
		return res;
	}

	static Matrix exp(Matrix base, long long exp) {
		Matrix res(base.n, base.n);
		for (int i = 0; i < res.n; i++) {
			res[i][i] = 1;
    }
		while (exp > 0) {
			if (exp & 1) res = res * base;
			base = base * base;
			exp >>= 1;
		}
		return res;
	}
};