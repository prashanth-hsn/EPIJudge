#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> NextPermutation(vector<int> perm) {
    auto inversion_point = std::is_sorted_until(perm.rbegin(), perm.rend());
    if (inversion_point == perm.rend()) {
        return {};
    }
    auto least_upper_bound = std::upper_bound(perm.rbegin(), inversion_point, *inversion_point);
    std::iter_swap(inversion_point, least_upper_bound);
    std::reverse(perm.rbegin(), inversion_point);
    return perm;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm"};
  return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
                         &NextPermutation, DefaultComparator{}, param_names);
}
