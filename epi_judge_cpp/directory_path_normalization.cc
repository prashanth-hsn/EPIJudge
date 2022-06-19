#include <string>
#include <vector>
#include<sstream>

#include "test_framework/generic_test.h"

using std::string;
using std::vector;
string ShortestEquivalentPath(const string& path) {
  
    if (path.empty()) {
        throw std::invalid_argument("Empty string!");
    }

    vector<string> path_names;
    std::istringstream ss{ path };

    if (path.front() == '/') {
        path_names.push_back("/");
    }
    string token;
    while (std::getline(ss, token, '/')) {
        if (token == "..") {
            if (path_names.empty() || path_names.back() == "..") {
                path_names.push_back(token);
            }
            else {
                if (path_names.back() == "/") {
                    throw std::invalid_argument("Path error!");
                }
                path_names.pop_back();
            }
        }
        else if ((token != ".") && (token != "")) {
            path_names.push_back(token);
        }
    }
    string result{};
    if (!path_names.empty()) {
        result = path_names[0];
        for (int i = 1; i < path_names.size(); ++i) {
            if (i == 1 && result == "/") {
                result += path_names[i];
            }
            else {
                result += "/" + path_names[i];
            }
        }
    }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}
