#include "test_framework/generic_test.h"
bool IsPalindromeNumber(int x) {

    if (x <= 0)
        return x == 0;
    int numdigits = static_cast<int>(floor(log10(x))) + 1;
    int msdMask = static_cast<int>(pow(10, numdigits - 1));
    for (int i = 0; i < numdigits / 2; ++i)
    {
        if (x / msdMask != x % 10)
            return false;
        x %= msdMask;
        x /= 10;
        msdMask /= 100;
    }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "is_number_palindromic.cc",
                         "is_number_palindromic.tsv", &IsPalindromeNumber,
                         DefaultComparator{}, param_names);
}
