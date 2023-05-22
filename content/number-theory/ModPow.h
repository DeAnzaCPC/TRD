/**
 * Author: Sunho
 * Description:
 * Status: tested
 */
#pragma once

ll binexp(ll b, ll n) {
	ll res = 1;
	for (; n; b = b * b % MOD, n /= 2)
		if (n & 1) res = res * b % MOD;
	return res;
}
