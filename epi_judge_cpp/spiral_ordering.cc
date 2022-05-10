#include <vector>
#include <array>

#include "test_framework/generic_test.h"
using std::vector;
using std::array;
void GetSpiralOrder(const vector<vector<int>>& square_matrix, vector<int>& spiral_order, int index) {

    if (index == square_matrix.size() - index - 1) {
        spiral_order.push_back(square_matrix[index][index]);
        return;
    }
    // top
    for (int i = index; i < square_matrix.size() - index - 1; ++i) {
        spiral_order.push_back(square_matrix[index][i]);
    }
    // right
    for (int i = index; i < square_matrix.size() - index - 1; ++i) {
        spiral_order.push_back(square_matrix[i][square_matrix.size() - index - 1]);
    }
    // bottom
    for (int i = square_matrix.size() - index - 1; i > index; --i) {
        spiral_order.push_back(square_matrix[square_matrix.size() - index - 1][i]);
    }
    // left
    for (int i = square_matrix.size() - index - 1; i > index; --i) {
        spiral_order.push_back(square_matrix[i][index]);
    }
}

vector<int> MatrixInSpiralOrder(vector<vector<int>> square_matrix) {
    const array<array<int, 2>, 4> kshift = { {{0,1}, {1,0}, {0, -1 }, {-1, 0}} };
    int dir = 0, x = 0, y = 0;
    vector<int> spiral_order;
    for (int i = 0; i < square_matrix.size() * square_matrix.size(); ++i) {
        spiral_order.push_back(square_matrix[x][y]);
        square_matrix[x][y] = 0;
        int next_x = x + kshift[dir][0], next_y = y + kshift[dir][1];
        if (next_x < 0 || next_x >= square_matrix.size() ||
            next_y < 0 || next_y >= square_matrix.size() ||
            square_matrix[next_x][next_y] == 0) {
            dir = (dir + 1) % 4;
            next_x = x + kshift[dir][0];
            next_y = y + kshift[dir][1];
        }
        x = next_x, y = next_y;
    }
    return spiral_order;
}

vector<int> MatrixInSpiralOrder1(const vector<vector<int>>& square_matrix) {
    vector<int> spiral_order;
    int boundary_size = ceil(square_matrix.size() * 0.5);
    for(int index = 0; index < boundary_size; ++index) {
        GetSpiralOrder(square_matrix, spiral_order, index);
    }
  return spiral_order;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
