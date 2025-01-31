#include <string>
#include <numeric>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  
    if (!x)
        return "0";
    bool isnegative = (x < 0)? true: false;
    x = abs(x);
    string number;    
    while (x) {
        int digit = x % 10;
        char d = '0' + digit;
        number.push_back(d);
        x /= 10;
    }

    if (isnegative)
        number.push_back('-');
    
    return { rbegin(number), rend(number) };
}
int StringToInt(const string& s) {
    return (s[0] == '-' ? -1 : 1) * std::accumulate(s.begin() + (s[0] == '-' || s[0] == '+'), s.end(), 0, [](int running_sum, char c) { return running_sum * 10 + c - '0'; });
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
