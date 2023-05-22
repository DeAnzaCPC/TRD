/**
 * Author: Håkan Terelius
 * Date: 2009-09-25
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Euler's_totient_function
 * Description: \emph{Euler's $\phi$} function is defined as $\phi(n):=\#$ of positive integers $\leq n$ that are coprime with $n$.
 *  This template can be used to calculate any multiplicative function (e.g. mobius)
 * $\phi(1)=1$, $p$ prime $\Rightarrow \phi(p^k)=(p-1)p^{k-1}$, $m,n$ coprime $\Rightarrow \phi(mn)=\phi(m)\phi(n)$.
 * If $n=p_1^{k_1}p_2^{k_2} ... p_r^{k_r}$ then $\phi(n) = (p_1-1)p_1^{k_1-1}...(p_r-1)p_r^{k_r-1}$.
 * $\phi(n)=n \cdot \prod_{p|n}(1-1/p)$.
 * $\sum_{d|n} \phi(d) = n$, $\sum_{1\leq k \leq n, \gcd(k,n)=1} k = n \phi(n)/2, n>1$
 *
 * \textbf{Euler's thm}: $a,n$ coprime $\Rightarrow a^{\phi(n)} \equiv 1 \pmod{n}$.
 *
 * \textbf{Fermat's little thm}: $p$ prime $\Rightarrow a^{p-1} \equiv 1 \pmod{p}$ $\forall a$.
 * 
 * Status: Tested
 */
#pragma once

vector<int>prime;
bool is_prime[MAXN];
int phi[MAXN];

void sieve () {
	fill(is_prime + 2, is_prime + MAXN, true);
	phi[1] = 1;
	for (int i = 2; i < MAXN; ++i) {
		if (is_prime[i]) {
			prime.push_back (i);
			phi[i] = i - 1;	//i is prime
		}
		for (int j = 0; j < prime.size () && i * prime[j] < MAXN; ++j) {
			is_prime[i * prime[j]] = false;
			if (i % prime[j] == 0) {
				// use transition
				phi[i * prime[j]] = phi[i] * prime[j];	// prime[j] divides i
				break;
			} else {
				// use multiplicative property
				phi[i * prime[j]] = phi[i] * phi[prime[j]];	//prime[j] does not divide i
			}
		}
	}
}