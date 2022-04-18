#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
bool CanReachEnd(const vector<int>& max_advance_steps) {
    int farthest_index = 0, last_index = max_advance_steps.size() - 1;
    for (int i = 0; i <= farthest_index && farthest_index < last_index; ++i) {
        farthest_index = std::max(farthest_index, max_advance_steps[i] + i);
    }

  return farthest_index >= last_index;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}
