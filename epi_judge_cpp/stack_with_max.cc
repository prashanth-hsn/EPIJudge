#include <stdexcept>
#include<stack>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
using std::length_error;
using std::stack;

class Stack {
public:
    bool Empty() const {
        return m_elementStack.empty();
    }
    int Max() const {
        return m_elementStack.top().m_max;
    }
    int Pop() {
        int ret = m_elementStack.top().m_element;
        m_elementStack.pop();
        return ret;
    }
    void Push(int x) {
        m_elementStack.emplace(x, std::max(x, (Empty()) ? x : m_elementStack.top().m_max));
    }
private:
    struct ElementWithMaxCache {
        int m_element;
        int m_max;
    };
    stack<ElementWithMaxCache> m_elementStack;
};
struct StackOp {
    std::string op;
    int argument;
};

namespace test_framework {
    template <>
    struct SerializationTrait<StackOp> : UserSerTrait<StackOp, std::string, int> {};
}  // namespace test_framework

void StackTester(const std::vector<StackOp>& ops) {
    try {
        Stack s;
        for (auto& x : ops) {
            if (x.op == "Stack") {
                continue;
            }
            else if (x.op == "push") {
                s.Push(x.argument);
            }
            else if (x.op == "pop") {
                int result = s.Pop();
                if (result != x.argument) {
                    throw TestFailure("Pop: expected " + std::to_string(x.argument) +
                        ", got " + std::to_string(result));
                }
            }
            else if (x.op == "max") {
                int result = s.Max();
                if (result != x.argument) {
                    throw TestFailure("Max: expected " + std::to_string(x.argument) +
                        ", got " + std::to_string(result));
                }
            }
            else if (x.op == "empty") {
                int result = s.Empty();
                if (result != x.argument) {
                    throw TestFailure("Empty: expected " + std::to_string(x.argument) +
                        ", got " + std::to_string(result));
                }
            }
            else {
                throw std::runtime_error("Unsupported stack operation: " + x.op);
            }
        }
    }
    catch (length_error&) {
        throw TestFailure("Unexpected length_error exception");
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{ argv + 1, argv + argc };
    std::vector<std::string> param_names{ "ops" };
    return GenericTestMain(args, "stack_with_max.cc", "stack_with_max.tsv",
        &StackTester, DefaultComparator{}, param_names);
}
