#include <string>
#include <numeric>

#include "test_framework/generic_test.h"
using std::string;

string ConstructFromBase (int num_as_int, int base) {
    return (num_as_int == 0) ? "" : ConstructFromBase(num_as_int/base, base) + (char)((num_as_int % base >= 10)? ('A' + num_as_int % base - 10) : ('0' + num_as_int % base));
}

string ConvertBase(const string& num_as_string, int b1, int b2) {

    string ret = "";
    if (num_as_string.empty())
        return ret;
    if (num_as_string == "0")
        return num_as_string;

  int num_in_decimal = std::accumulate(num_as_string.begin() + (num_as_string[0] == '-' || num_as_string[0] == '+'), num_as_string.end(), 0,
          [b1] (int running_sum, char ch) { return running_sum * b1 + (isdigit(ch)? ch - '0' : ch - 'A' + 10); });

  bool is_negative = num_as_string[0] == '-';

  return ((is_negative)? "-" : "") + ConstructFromBase(num_in_decimal, b2);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
