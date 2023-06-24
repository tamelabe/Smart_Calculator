#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include "../resources/exprtk.hpp"
#include <stack>
#include <queue>

namespace s21 {
    class Model {
    public:
        void calculate(std::string &expr, const std::string &x_def) {
//            this->expr = expr;
//            this->expr_x = x_def;
            if (!validate(expr)) return;
        }
    private:
//        std::string res_;
//        std::string expr;
//        std::string expr_x;
        void infixToPrefix(const std::string &expr) {
            std::stack<std::string> op_stack;
            std::queue<std::string> qu_output;

        }

        int priority() {

        }
        bool validate(std::string &expr) {
            size_t pos = expr.find("mod");
            while (pos != std::string::npos) {
                expr.replace(pos, 3, "%");
                pos = expr.find("mod", pos + 1);
            }

            exprtk::symbol_table<double> symbol_table;
            exprtk::expression<double> expression;
            exprtk::parser<double> parser;

            symbol_table.add_constants();
            double x;
            symbol_table.add_variable("x", x);
            expression.register_symbol_table(symbol_table);
            expr.erase(std::remove(expr.begin(), expr.end(), ' '), expr.end());

            if (parser.compile(expr, expression))
            {
//                expr = std::to_string(expression.value());
                return 1;
            } else {
                expr =  "Error";
                return 0;
            }
        }
    };
} // namespace s21

#endif  // SRC_MODEL_MODEL_H_
