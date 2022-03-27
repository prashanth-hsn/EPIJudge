#include "test_framework/generic_test.h"
unsigned long long ClosestIntSameBitCount(unsigned long long x) {
  
    short numBits = sizeof(x) * 8;

    for (short i = 0; i < numBits - 1; ++i)
    {
        if (((x>> i) & 1) != ((x >> (i + 1)) & 1))
        {
            return x ^= ((1L << i) | (1L << (i + 1)));
        }
    }

//  throw TestFailure("All bit are 0 or 1");
    return 0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "closest_int_same_weight.cc",
                         "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                         DefaultComparator{}, param_names);
}
