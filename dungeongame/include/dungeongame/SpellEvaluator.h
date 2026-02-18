#pragma once

#include <string>

namespace dungeongame {

// Minimal postfix (RPN) expression evaluator used for Week 04 spell demo.
// Supports integer operands and + - * / operators (integer division).
// Throws std::invalid_argument on malformed input or divide-by-zero.
class SpellEvaluator {
public:
    static int evaluatePostfix(const std::string& expr);
};

} // namespace dungeongame
