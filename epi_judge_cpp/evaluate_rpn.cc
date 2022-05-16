#include <string>
#include <unordered_map>
#include <functional>
#include "test_framework/generic_test.h"
#include <sstream>
#include <stack>

using std::string;
using std::unordered_map;
using std::function;
using std::stack;

int Evaluate(const string& expression) {
    const unordered_map<string, function <int(int, int)>> kOperator = 
   {{"+", [](int a, int b)->int { return a + b; }},
    {"-", [](int a, int b)->int { return a - b; }},
    {"*", [](int a, int b)->int { return a * b; }},
    {"/", [](int a, int b)->int { return a / b; }}};

    std::stringstream stream(expression);
    stack<int> intermediate_result;
    string token;
    const char delimiter = ',';
    while (std::getline(stream, token, delimiter)) {
        if (kOperator.count(token)) {
            // the order of a and b is important. lifo.
            int b = intermediate_result.top(); 
            intermediate_result.pop();
            int a = intermediate_result.top();
            intermediate_result.pop();
            int result = kOperator.at(token)(a, b);
            intermediate_result.emplace(result);
        } 
        else {
            intermediate_result.emplace(std::stoi(token));
        }
    }

  return intermediate_result.top();
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
