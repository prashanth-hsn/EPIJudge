#include <array>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
enum class Color { kRed, kWhite, kBlue };

void DutchFlagPartition1(int pivot_index, vector<Color>* A_ptr) {
  
    vector<Color>& A = *A_ptr;
    Color pivot = A[pivot_index];
    for (auto i = 0; i < A.size(); ++i) {
        for (auto j = i + 1; j < A.size(); ++j) {
            if (A[j] < pivot) {
                std::swap(A[i], A[j]);
                break;
            }
        }
    }

    for (long int i = A.size() - 1; i >= 0; --i) {
        for (long int j = i - 1; j >= 0; --j) {
            if (A[j] > pivot) {
                std::swap(A[i], A[j]);
                break;
            }
        }
    }
  return;
}



void DutchFlagPartition2(int pivot_index, vector<Color>* A_ptr) {

    vector<Color>& A = *A_ptr;
    Color pivot = A[pivot_index];
    int lower = 0;
    for (auto i = 0; i < A.size(); ++i) {
        if (A[i] < pivot) {
            std::swap(A[i], A[lower++]);
        }
    }
    int upper = std::size(A) - 1;
    for (long int i = std::size(A) - 1; i >= 0; --i) {
        if (A[i] > pivot) {
            std::swap(A[i], A[upper--]);
        }
    }
    return;
}


void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {

    vector<Color>& A = *A_ptr;
    Color pivot = A[pivot_index];
    int smaller = 0, equal = 0, larger = std::size(A);
    while ( equal < larger ) {
        if (A[equal] < pivot) {
            std::swap(A[equal++], A[smaller++]);
        }
        else if (A[equal] == pivot) {
            ++equal;
        }
        else {
            std::swap(A[equal], A[--larger]);
        }
    }
    return;
}

void DutchFlagPartitionWrapper(TimedExecutor& executor, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  executor.Run([&] { DutchFlagPartition(pivot_idx, &colors); });

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[static_cast<int>(colors[i])]--;
    ++i;
  }

  if (i != colors.size()) {
    throw TestFailure("Not partitioned after " + std::to_string(i) +
                      "th element");
  } else if (count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailure("Some elements are missing from original array");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "A", "pivot_idx"};
  return GenericTestMain(args, "dutch_national_flag.cc",
                         "dutch_national_flag.tsv", &DutchFlagPartitionWrapper,
                         DefaultComparator{}, param_names);
}
