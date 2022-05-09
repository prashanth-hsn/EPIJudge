#include <vector>
#include <deque>
#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
    if (n < 2) {
        return {};
    }

    std::vector<int> primes;
    primes.push_back(2);
    const int size = floor(0.5 * (n - 3)) + 1;
    std::deque<bool> is_prime(size, true);

    for (int i = 0; i < size; ++i) {
        if (is_prime[i]) {
            int p = (i * 2) + 3;
            primes.push_back(p);
            for (long long j = 2LL * i * i + 6 * i + 3; j < size; j += p) {
                is_prime[j] = false;
            }
        }
    }
  return primes;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
