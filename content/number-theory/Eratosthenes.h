/**
 * Author: Ralph
 * Description: Prime sieve for generating all primes up to a certain limit.
 */
#define SIEVE_SIZE 10000000

bool isPrime[SIEVE_SIZE+1];
int spf[SIEVE_SIZE+1]; //smallest prime factor
vector<int> primes;

void sieve() {
  fill(begin(isPrime) + 2, end(isPrime), true);
	for (int i = 2; i <= SIEVE_SIZE; i++) {
		if (isPrime[i]) {
			primes.push_back(i);
			spf[i] = i;
		}
		for (int j = 0; j < primes.size() && i * primes[j] <= SIEVE_SIZE && primes[j] <= spf[i]; j++) {
			isPrime[i * primes[j]] = false;
			spf[i * primes[j]] = primes[j];
		}
	}
}
