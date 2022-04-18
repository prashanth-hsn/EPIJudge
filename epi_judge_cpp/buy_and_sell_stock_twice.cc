#include <vector>
#include <limits.h>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockTwice(const vector<double>& prices) {
    if (prices.empty())
        return 0.0;
    double min_price = prices[0];
    double max_profit = 0;
    std::vector<double> profits(prices.size(), 0);
    for (int i = 0; i < prices.size(); ++i) {
        min_price = std::min(min_price, prices[i]);
        max_profit = std::max(max_profit, prices[i] - min_price);
        profits[i] = max_profit;
    }

    double max_price = prices.back();
    for (int i = prices.size() - 1; i > 0; --i) {
        max_price = std::max(max_price, prices[i]);
        max_profit = std::max(max_profit, profits[i - 1] + max_price - prices[i]);
    }
  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
