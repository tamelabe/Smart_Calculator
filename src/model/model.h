#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include "../resources/exprtk.hpp"
#include <stack>
#include <queue>
#include <cmath>
#include <sstream>

namespace s21 {
    class Model {
    public:
        Model() {

        }
        void calculate(std::string &expr, const std::string &x_def) {
            if (!validate(expr)) return;
            infixToPostfix(expr);
            postfixCalc(expr);
        }
    private:
        std::map<std::string, int> priorities_ {
          {"sin", 0}, {"cos", 0}, {"tan", 0}, {"asin", 0}, {"acos", 0}, {"atan", 0}, {"sqrt", 0}, {"log", 0}, {"log10", 0},
          {"(", 1}, {")", 1},
          {"^", 2},
          {"*", 4}, {"/", 4}, {"%", 4},
          {"+", 5}, {"-", 5}, {"~", 5}
        };
        std::string functions_ = "sin cos tan asin acos atan sqrt log10 log";
        std::queue<std::string> postfix_q_;

        void infixToPostfix(std::string &expr) {
            std::stack<std::string> operators;
            bool unary_ind = true;
            for (auto i = 0; i < expr.length();) {
                if (unary_ind && expr[i] == '-') {
                    operators.emplace(1, '~');
                    ++i;
                } else if (unary_ind && expr[i] == '+') {
                    ++i;
                }
                if (std::isdigit(expr[i]) || expr[i] == '.' || expr[i] == 'e') {
                    postfix_q_.push(extractDigit(expr, i));
                    unary_ind = false;
                } else if (int str_len = detFunction(expr, i)) {
                    operators.push(expr.substr(i, str_len));
                    i += str_len;
                    unary_ind = false;
                } else if (expr[i] == '(') {
                    operators.emplace(1, expr[i++]);
                    unary_ind = true;
                } else if (expr[i] == ')') {
                    while (!operators.empty() && operators.top() != "(") {
                        postfix_q_.push(operators.top());
                        operators.pop();
                    }
                    if (!operators.empty() && operators.top() == "(") {
                        operators.pop();
                    }
                    i++;
                    unary_ind = false;
                } else {
                    while (!operators.empty() && operators.top() != "(" && getPriority(operators.top()) <= getPriority(std::string(1, expr[i]))) {
                        if (expr[i] == '^' && operators.top() == "^") {
                            break;
                        }
                        postfix_q_.push(operators.top());
                        operators.pop();
                    }
                    operators.emplace(1, expr[i]);
                    i++;
                    unary_ind = true;
                    }
                }
            while (!operators.empty()) {
                postfix_q_.push(operators.top());
                operators.pop();
            }
        }

        void postfixCalc(std::string &expr) {
            std::stack<double> nums;
            bool is_number = false;
            while (!postfix_q_.empty()) {
                try {
                    nums.push(std::stod(postfix_q_.front()));
                    is_number = true;
                    postfix_q_.pop();
                } catch (const std::exception& e) {
                    is_number = false;
                }
                if (!is_number) {
                    double num_first = nums.top();
                    if (detFunction(postfix_q_.front())) {
                        pushNumToStack(nums, calcFunctions(num_first));
                    } else if (postfix_q_.front() == "~") {
                        num_first *= -1;
                        pushNumToStack(nums, num_first);
                    } else if (nums.size() > 1) {
                        nums.pop();
                        double value = nums.top();
                        value = calcOperators(value, num_first, postfix_q_.front());
                        pushNumToStack(nums, value);
                    }
                }
            }
            strToDouble(nums, expr);
        }

        void strToDouble(const std::stack<double> &nums, std::string &expr) {
            std::ostringstream stream;
            stream.precision(8);
            stream << std::fixed << nums.top();
            expr = stream.str();
            size_t iter = expr.find_last_not_of('0');
            if (expr[iter] == '.') { --iter; }
            expr = expr.substr(0, ++iter);
        }

        void pushNumToStack(std::stack<double> &nums, double value) {
            nums.pop();
            nums.push(value);
            postfix_q_.pop();
        }

        double calcFunctions(const int &num) {
            std::map<std::string, std::function<double(double)>> functions_call_;
            functions_call_["sin"] = static_cast<double(*)(double)>(std::sin);
            functions_call_["cos"] = static_cast<double(*)(double)>(std::cos);
            functions_call_["tan"] = static_cast<double(*)(double)>(std::tan);
            functions_call_["asin"] = static_cast<double(*)(double)>(std::asin);
            functions_call_["acos"] = static_cast<double(*)(double)>(std::acos);
            functions_call_["atan"] = static_cast<double(*)(double)>(std::atan);
            functions_call_["sqrt"] = static_cast<double(*)(double)>(std::sqrt);
            functions_call_["log"] = static_cast<double(*)(double)>(std::log);
            functions_call_["log10"] = static_cast<double(*)(double)>(std::log10);
            auto iter = functions_call_.find(postfix_q_.front());
            return iter->second(num);
        }
        
        double calcOperators(const double &lhs, const double &rhs, const std::string &op) {
            if (op == "+") {
                return lhs + rhs;
            } else if (op == "-") {
                return lhs - rhs;
            } else if (op == "*") {
                return lhs * rhs;
            } else if (op == "/") {
                return lhs / rhs;
            } else if (op == "%") {
                return std::fmod(lhs, rhs);
            } else if (op == "^") {
                return pow(lhs, rhs);
            } else {
                return 0;
            }
        }

        std::string extractDigit(const std::string &expr, int &i) {
            int start = i;
            for (;i < expr.length() && (std::isdigit(expr[i]) || expr[i] == '.'); ++i) {
            }
            return expr.substr(start, i - start);
        }
        int detFunction(const std::string &expr, size_t pos = 0) const {
            std::string f_name;
            int size = 0;
            for (;pos < expr.size() && std::isalpha(expr[pos]); ++pos)
                f_name.push_back(expr[pos]);
            if (expr.size() > pos + 1 && expr.substr(pos, 2) == "10")
                size = 2;
            if (functions_.find(f_name) == std::string::npos)
                 return 0;
            return static_cast<int>(f_name.length()) + size;
        }

        int getPriority(std::string token) {
            try {
                return priorities_.at(token);
            } catch (const std::exception &e) {
                return -1;
            }
        }

        void replace(std::string &expr, std::string old_s, std::string new_s) {
            size_t pos = expr.find(old_s);
            while (pos != std::string::npos) {
                expr.replace(pos, old_s.length(), new_s);
                pos = expr.find(old_s, pos + 1);
            }
        }
        bool validate(std::string &expr) {
            replace(expr, "log", "log10");
            replace(expr, "ln", "log");
            replace(expr, "mod", "%");

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
                return true;
            } else {
                expr = "Error";
                return false;
            }
        }
    };
} // namespace s21

#endif  // SRC_MODEL_MODEL_H_
