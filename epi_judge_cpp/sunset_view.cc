#include <iterator>
#include <vector>
#include <stack>

#include "test_framework/generic_test.h"
using std::vector;
using std::stack;
vector<int> ExamineBuildingsWithSunset(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end) {
  
    struct BuildHeightIndex{
        int idx;
        int height;
    };
    stack<BuildHeightIndex> candidates;
    int index = 0;
    while (sequence_begin != sequence_end) {
        int height = *sequence_begin++;
        while (!candidates.empty() && (candidates.top().height <= height)) {
            candidates.pop();
        }
        candidates.emplace(index, height);
        index++;
    }

    vector<int> result;
    while (!candidates.empty()) {
        result.push_back(candidates.top().idx);
        candidates.pop();
    }
  return result;
}
vector<int> ExamineBuildingsWithSunsetWrapper(const vector<int>& sequence) {
  return ExamineBuildingsWithSunset(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "sunset_view.cc", "sunset_view.tsv",
                         &ExamineBuildingsWithSunsetWrapper,
                         DefaultComparator{}, param_names);
}
