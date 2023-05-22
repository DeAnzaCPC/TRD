/**
 * Author: Ralph
 * Description: Fenwick tree for partial sum.
 * Time: Both operations are $O(\log N)$.
 */
#define SIZE 1000

long long bit[SIZE];

long long sum(int i) { // sum of [1,i]
	long long sum = 0;
	while (i > 0) {
		sum += bit[i];
		i -= (i) & -(i);
	}
	return sum;
}

void add(int i, long long delta) {
	while (i <= SIZE) {
		bit[i] += delta;
		i += (i) & -(i);
	}
}