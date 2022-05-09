#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<vector<int>> GeneratePascalTriangle(int num_rows) {
    vector<vector<int>> pascals_triangle;

    for (int i = 0; i < num_rows; ++i) {
        vector<int> current_row(i + 1);
        for (int j = 0; j < i + 1; ++j) {
            current_row[j] = (j > 0 && j < i) ? pascals_triangle[i - 1][j - 1] + pascals_triangle[i - 1][j] : 1;
        }
        pascals_triangle.push_back(current_row);
    }
  return pascals_triangle;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_rows"};
  return GenericTestMain(args, "pascal_triangle.cc", "pascal_triangle.tsv",
                         &GeneratePascalTriangle, DefaultComparator{},
                         param_names);
}
