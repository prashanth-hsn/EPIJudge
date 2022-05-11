#include <string>
#include <numeric>

#include "test_framework/generic_test.h"
using std::string;

int SSDecodeColID(const string& col) {
    return std::accumulate(col.begin(), col.end(), 0, [] (int running_sum, char ch) { return running_sum * 26 + ch - 'A' + 1; });
  return 0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"col"};
  return GenericTestMain(args, "spreadsheet_encoding.cc",
                         "spreadsheet_encoding.tsv", &SSDecodeColID,
                         DefaultComparator{}, param_names);
}
