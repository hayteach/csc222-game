#include "dungeongame/SpellEvaluator.h"
#include <sstream>
#include <stack>
#include <stdexcept>

namespace dungeongame {

int SpellEvaluator::evaluatePostfix(const std::string& expr)
{
    std::istringstream in(expr);
    std::stack<int> st;
    std::string token;

    while (in >> token) {
        // if token is an operator
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (st.size() < 2) throw std::invalid_argument("Malformed postfix expression");
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            int res = 0;
            if (token == "+") res = a + b;
            else if (token == "-") res = a - b;
            else if (token == "*") res = a * b;
            else {
                if (b == 0) throw std::invalid_argument("Division by zero");
                res = a / b;
            }
            st.push(res);
        } else {
            // try to parse integer (supports negative numbers)
            try {
                size_t idx = 0;
                int val = std::stoi(token, &idx);
                if (idx != token.size()) throw std::invalid_argument("Invalid token");
                st.push(val);
            } catch (...) {
                throw std::invalid_argument("Invalid token in postfix expression: '" + token + "'");
            }
        }
    }

    if (st.size() != 1) throw std::invalid_argument("Malformed postfix expression");
    return st.top();
}

} // namespace dungeongame
