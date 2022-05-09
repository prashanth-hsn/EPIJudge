#include <vector>
#include<deque>
#include "test_framework/generic_test.h"
using std::vector;
using std::deque;

bool HasDuplicate(const vector<vector<int>>& partial_assignment, int start_row, int end_row, int start_col, int end_col) {
    deque<bool> is_present(size(partial_assignment) + 1, false);
    for (int i = start_row; i < end_row; ++i) {
        for (int j = start_col; j < end_col; ++j) {
            if (partial_assignment[i][j] != 0 && is_present[partial_assignment[i][j]]) {
                return true;
            }
            is_present[partial_assignment[i][j]] = true;
        }
    }
    return false;
}

// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  
    // Row?
    for (int i = 0; i < size(partial_assignment); ++i) {
        if (HasDuplicate(partial_assignment, i, i + 1, 0, size(partial_assignment))) {
            return false;
        }
    }

    // Column ?
    for (int i = 0; i < size(partial_assignment); ++i) {
        if (HasDuplicate(partial_assignment, 0, size(partial_assignment), i, i + 1)) {
            return false;
        }
    }

    // Region
    int region_size = sqrt(size(partial_assignment));
    for (int i = 0; i < region_size; ++i) {
        for (int j = 0; j < region_size; ++j) {
            if (HasDuplicate(partial_assignment, i * region_size, (i + 1) * region_size, j * region_size, (j + 1) * region_size)) {
                return false;
            }
        }
    }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
