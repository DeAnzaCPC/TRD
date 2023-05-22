/**
 * Author: Ralph
 * Description: Arbitrary mod ntt(a) computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, where $g=\text{root}^{(mod-1)/N}$.
 * N must be a power of 2. MOD is $4*10^{17}$ for default setting.
 * Time: O(N \log N)
 */
const long long MOD1 = 998244353ll; // 2^23 * 7 * 17 + 1
const long long MOD2 = 469762049ll; // 2^26 * 7 + 1
// 167772161 = 2^25 * 5 + 1
// 7340033 = 2^20 * 7 + 1
// 3 is primitive root for all
NTTHelper<MOD1> helper1;
NTTHelper<MOD2> helper2;

vector<long long> multiply(vector<long long> a, vector<long long> b) {
  int sz = 1 << (sizeof(int) * 8 - __builtin_clz(a.size() + b.size() - 2));
  a.resize(sz), b.resize(sz);
  vector<long long> res1 = helper1.multiply(a, b);
  vector<long long> res2 = helper2.multiply(a, b);
  res1.resize(a.size() + b.size() - 1), res2.resize(a.size() + b.size() - 1);

  __int128_t p1 = 260520730147305702, p2 = 208416582520653596, mod = (__int128_t)MOD1*MOD2;
  vector<long long> res(res1.size());
  for (int i = 0; i < res.size(); i++) {
    res[i] = (res1[i] * p1 + res2[i] * p2) % mod;
  }
  return res;
}

