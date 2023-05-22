/**
 * Author: Sunho
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 */
#pragma once

const int MOD = 1000000007; // 998244353
struct mint {
  int x;
  mint(int x = 0) : x(norm(x)) { }
  mint(ll x) : x(norm(x%MOD)) { }
  int norm(int x) const { if (x < 0) { x += MOD; } if (x >= MOD) { x -= MOD; } return x; }
  mint operator+(mint o) const { return norm(x + o.x); }
  mint operator-(mint o) const { return norm(x - o.x); }
  mint operator*(mint o) const { return ll(x) * o.x; }
	mint operator/(mint o) { return *this * o.inv(); }
  mint inv() const { return exp(MOD - 2); }
	mint exp(ll n) {
		if (!n) return mint(1);
		mint a = *this;
		mint r = a.exp(n / 2); r = r * r;
		return n&1 ? a * r : r;
	}
};