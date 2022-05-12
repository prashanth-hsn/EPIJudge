#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsPalindrome(const string& s) {
  int index_fwd = 0, index_back = s.size() - 1;
  while (index_fwd < index_back)
  {
      while (!isalnum(s[index_fwd]) && index_fwd < index_back)
          ++index_fwd;
      while (!isalnum(s[index_back]) && index_fwd < index_back )
          --index_back;

      if (tolower(s[index_fwd++]) != tolower(s[index_back--]))
          return false;
  }
  return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_palindromic_punctuation.cc",
                         "is_string_palindromic_punctuation.tsv", &IsPalindrome,
                         DefaultComparator{}, param_names);
}
