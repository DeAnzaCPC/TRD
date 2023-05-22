/**
 * Author: Ralph
 * Description: ntt(a) computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, where $g=\text{root}^{(mod-1)/N}$.
 * N must be a power of 2.
 * Time: O(N \log N)
 */
#define MOD 998244353
template<long long P>
struct NTTHelper {
	static const int sz = 1 << 20;
	long long omega[sz];

	NTTHelper() {
		omega[sz / 2] = 1;
		long long exp = 1, base = 3, pow = P / sz;
		while (pow) {
			if (pow & 1)
				exp = exp * base % P;
			base = base * base % P;
			pow >>= 1;
		}
		for (int i = sz / 2 + 1; i < sz; i++)
			omega[i] = omega[i - 1] * exp % P;
		for (int i = sz / 2 - 1; i > 0; i--)
			omega[i] = omega[i << 1];
	}
	
	void ntt(long long *arr, int m) {
		if (m == 1)
			return;
		ntt(arr, m / 2);
		ntt(arr + m / 2, m / 2);
		for (int i = 0; i < m / 2; i++) {
			long long e = arr[i], o = omega[i + m / 2] * arr[i + m / 2] % P;
			arr[i] = e + o < P ? e + o : e + o - P;
			arr[i + m / 2] = e - o >= 0 ? e - o : e - o + P;
		}
	}

	void ntt(vector<long long> &arr, bool inverse) {
		int m = arr.size();
		for (int i = 1, j = 0; i < m; i++) {
			int bit = m >> 1;
			for (; j & bit; bit >>= 1)
				j ^= bit;
			j ^= bit;

			if (i < j)
				swap(arr[i], arr[j]);
		}
		ntt(arr.data(), m);
		if (inverse)
		{
			reverse(arr.begin() + 1, arr.end());
			for (int i = 0; i < m; i++)
				arr[i] = arr[i] * (P - P / m) % P;
		}
	}

	vector<long long> multiply(vector<long long> a, vector<long long> b) {
		ntt(a, false);
		ntt(b, false);
		vector<long long> res(a.size());
		for (int i = 0; i < res.size(); i++) {
			res[i] = a[i] * b[i] % P;
		}
		ntt(res, true);
		return res;
	}
};
NTTHelper<MOD> helper;

vector<long long> multiply(vector<long long> a, vector<long long> b) {
	int sz = 1 << (sizeof(int) * 8 - __builtin_clz(a.size() + b.size() - 2));
	a.resize(sz), b.resize(sz);
	vector<long long> res = helper.multiply(a, b);
	res.resize(a.size() + b.size() - 1);
	return res;
}