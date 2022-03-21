#include "test_framework/generic_test.h"
#include "utils/utils.h"

short computParity(int num)
{
    short result = 0;
    while (num)
    {
        result ^= 1;
        num &= (num - 1);
    }
    return result;
}

short getParityFor16Bits(unsigned int x)
{
    static bool init = true;
    static short kPreComputedParity[65536];
    if (init)
    {
        for (int i = 0; i < 65536; ++i)
        {
            kPreComputedParity[i] = computParity(i);
        }
        init = false;
    }
    if (x >= 0 && x <= 65535)
        return kPreComputedParity[x];
    return 0;
}


short computParityTwo(unsigned long long x)
{
    x ^= x >> 32;
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;

    return x & 0x1;
}


short Parity(unsigned long long x) {
    //
    //const int kMaskSize = 16;
    //const int kBitMask = 0xFFFF; 
    //
    //auto x1 = x >> (3 * kMaskSize);
    //auto x2 = (x >> (2 * kMaskSize)) & kBitMask;
    //auto x3 = (x >> kMaskSize) & kBitMask;
    //auto x4 = x & kBitMask;
    ////printInBinary(x);
    ////printInBinary(x1);
    ////printInBinary(x2);
    ////printInBinary(x3);
    ////printInBinary(x4);

    //return getParityFor16Bits(x1) ^
    //    getParityFor16Bits(x2) ^
    //    getParityFor16Bits(x3) ^ 
    //    getParityFor16Bits(x4);
    return computParityTwo(x);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
