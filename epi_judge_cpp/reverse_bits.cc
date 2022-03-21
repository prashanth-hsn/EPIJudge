#include "test_framework/generic_test.h"
#include "utils/utils.h"

unsigned long long SwapBits(unsigned long long x, int i, int j) {

    if (((x >> i) & 1) != ((x >> j) & 1))
    {
        unsigned long long bitmask = (1LL << i) | (1LL << j);
        return x ^ bitmask;
    }

    return x;
}

unsigned long long reverseLookup[65536];
void compute16BitReverseLookup()
{
    for (unsigned long long i = 0; i < 65536; ++i)
    {
        reverseLookup[i] = i;
        for (int j = 0; j < 16/2; ++j)
        {
            reverseLookup[i] = SwapBits(reverseLookup[i], j, 15 - j);
        }
    }
}
unsigned long long ReverseBits(unsigned long long x) {
  
    int numbits = 16;
    unsigned int bitmask = 0xFFFF;

    unsigned long long x1 = (x >> numbits * 3);
    unsigned long long x2 = (x >> numbits * 2) & bitmask;
    unsigned long long x3 = (x >> numbits) & bitmask;
    unsigned long long x4 = x & bitmask;

    return ( reverseLookup[x1] |
        ( reverseLookup[x2] << numbits) |
        ( reverseLookup[x3] << numbits * 2) |
        ( reverseLookup[x4] << numbits * 3) );
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  compute16BitReverseLookup();
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
