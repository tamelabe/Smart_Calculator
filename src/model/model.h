#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include "../resources/exprtk.hpp"
#include <stack>
#include <queue>

namespace s21 {
    class Model {
    public:
        void calculate(std::string &expr, const std::string &x_def) {
            if (!validate(expr)) return;
            infixToPrefix(expr);
        }
//    private:
        std::map<std::string, int> priorities_ {
          {"sin", 0}, {"cos", 0}, {"tan", 0}, {"asin", 0}, {"acos", 0}, {"atan", 0}, {"sqrt", 0}, {"ln", 0}, {"log", 0},
          {"(", 1}, {")", 1},
          {"^", 2},
          {"*", 4}, {"/", 4}, {"%", 4},
          {"+", 5}, {"-", 5}
        };
        std::string functions_ = "sin cos tan asin acos atan sqrt ln log";

        void infixToPrefix(std::string &expr) {
            std::stack<std::string> operators;
            std::queue<std::string> rpn;
            for (auto i = 0; i < expr.length();) {
                if (std::isdigit(expr[i]) || expr[i] == '.') {
                    rpn.push(extractDigit(expr, i));

                } else if (int str_len = detFunction(expr, i)) {
                    operators.push(expr.substr(i, str_len));
                    i += str_len;
                } else if (expr[i] == '(') {
                    operators.push(std::string(1, expr[i++]));
                } else if (expr[i] == ')') {
                    std::cout << expr[i] << '\n';
                    while (!operators.empty() && operators.top() != "(") {
                        rpn.push(operators.top());
                        operators.pop();
                    }
                    if (!operators.empty() && operators.top() == "(") {
                        operators.pop();
                    }
                    i++;
                } else {
                    while (!operators.empty() && operators.top() != "(" && getPriority(operators.top()) <= getPriority(std::string(1, expr[i]))) {
                        rpn.push(operators.top());
                        operators.pop();
                    }
                    operators.push(std::string(1, expr[i]));
                    i++;
                    }
                }
            while (!operators.empty()) {
                rpn.push(operators.top());
                operators.pop();
            }
            expr = "";
            while (!rpn.empty()) {
                expr.append(rpn.front());
                rpn.pop();
            }
        }
        std::string extractDigit(const std::string &expr, int &i) {
            int start = i;
            for (;i < expr.length() && (std::isdigit(expr[i]) || expr[i] == '.'); ++i) {
            }
            return expr.substr(start, i - start);
        }
        size_t detFunction(const std::string &expr, int pos) {
            std::string f_name;
            for (;std::isalpha(expr[pos]); ++pos) { f_name.push_back(expr[pos]); }
            if (functions_.find(f_name) == std::string::npos)
                 return false;
             return f_name.length();
         }
        int getPriority(std::string token) {
            return priorities_.at(token);
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
                expr = "Error";
                return 0;
            }
        }
    };
} // namespace s21

#endif  // SRC_MODEL_MODEL_H_
