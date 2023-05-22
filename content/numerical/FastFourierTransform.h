/**
 * Author: Ralph
 * Description: fft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$. N must be a power of 2.
   Useful for convolution
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 */
using cd = complex<double>;

const double PI = atan(1) * 4;

struct FFTHelper {
	static const int sz = 1 << 20;
	cd omega[sz];
	FFTHelper() {
		omega[sz / 2] = 1;
		cd pow = exp(cd(0, 2 * PI / sz));
		for (int i = sz / 2 + 1; i < sz; i++)
			omega[i] = omega[i - 1] * pow;
		for (int i = sz / 2 - 1; i > 0; i--)
			omega[i] = omega[i << 1];
  }
    
	void fft(cd *arr, int m) {
		if (m == 1)
			return;
		fft(arr, m / 2);
		fft(arr + m / 2, m / 2);
		for (int i = 0; i < m / 2; i++) {
			cd e = arr[i], o = omega[i + m / 2] * arr[i + m / 2];
			arr[i] = e + o;
			arr[i + m / 2] = e - o;
		}
	}

	void fft(vector<cd> &arr, bool inverse) {
		int m = arr.size();
		for (int i = 1, j = 0; i < m; i++) {
			int bit = m >> 1;
			for (; j & bit; bit >>= 1)
				j ^= bit;
			j ^= bit;

			if (i < j)
				swap(arr[i], arr[j]);
		}
		fft(arr.data(), m);
		if (inverse) {
			reverse(arr.begin() + 1, arr.end());
			cd inv((double)1 / m, 0);
			for (int i = 0; i < m; i++)
				arr[i] = arr[i] * inv;
		}
	}

	vector<cd> multiply(vector<cd> a, vector<cd> b) {
		fft(a, false);
		fft(b, false);
		vector<cd> res(a.size());
		for (int i = 0; i < res.size(); i++) {
			res[i] = a[i] * b[i];
		}
		fft(res, true);
		return res;
	}
} helper;
