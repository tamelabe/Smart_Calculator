#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <cmath>
#include <queue>
#include <sstream>
#include <stack>
#include <unordered_map>

#include "../resources/exprtk.hpp"

namespace s21 {
class Model {
 public:
  Model() {}
  void calculate(std::string &expr, const std::string &x_def) {
    if (!validate(expr)) return;
    infixToPostfix(expr);
    postfixCalc(expr);
  }

 private:
  enum class Lexem : int {
    sin = 1,
    cos,
    tan,
    aSin,
    aCos,
    aTan,
    sqrt,
    log,
    log10,
    braceOp,
    braceCl,
    deg,
    mul,
    div,
    plus,
    minus,
    mod,
    unary,
    num
  };
  
  enum class LType : int {
    num,
    func,
    op
  };

  class Token {
   public:
    Token(LType type, Lexem name) : name_(name), type_(type), value_{} {}
    Token(LType type, Lexem name, double value) : name_(name), type_(type), value_(value) {}
    LType getType() const { return type_; }
    Lexem getName() const { return name_; }
    double getValue() const { return value_; }

   private:
    LType type_;
    Lexem name_;
    double value_;
  };

  std::unordered_map<std::string, Lexem> functions_{
      {"sin", Lexem::sin},   {"cos", Lexem::cos},   {"tan", Lexem::tan},
      {"asin", Lexem::aSin}, {"acos", Lexem::aCos}, {"atan", Lexem::aTan},
      {"sqrt", Lexem::sqrt}, {"log", Lexem::log},   {"log10", Lexem::log10}};

  std::unordered_map<char, Lexem> operators_{
      {'^', Lexem::deg}, {'*', Lexem::mul},  {'/', Lexem::div},
      {'%', Lexem::mod}, {'+', Lexem::plus}, {'-', Lexem::minus}};

  std::unordered_map<Lexem, int> priorities_{
      {Lexem::sin, 0},     {Lexem::cos, 0},     {Lexem::tan, 0},
      {Lexem::aSin, 0},    {Lexem::aCos, 0},    {Lexem::aTan, 0},
      {Lexem::sqrt, 0},    {Lexem::log, 0},     {Lexem::log10, 0},
      {Lexem::braceOp, 1}, {Lexem::braceCl, 1}, {Lexem::deg, 2},
      {Lexem::mul, 4},     {Lexem::div, 4},     {Lexem::mod, 4},
      {Lexem::plus, 5},    {Lexem::minus, 5},   {Lexem::unary, 5}};
  
  std::queue<Token> postfix_q_;

  void infixToPostfix(std::string &expr) {
    std::stack<Token> operators;
    bool unary_ind = true;
    for (size_t i = 0; i < expr.length();) {
      if (unary_ind && (expr[i] == '-' || expr[i] == '+')) {
        if (expr[i] == '-') operators.emplace(LType::op, Lexem::unary);
        ++i;
      }
      if (std::isdigit(expr[i]) || expr[i] == '.' || expr[i] == 'e') {
        postfix_q_.emplace(LType::num, Lexem::num, extractDigit(expr, i));
        unary_ind = false;
      } else if (int func_type = detFunction(expr, i)) {
        operators.emplace(LType::func, static_cast<Lexem>(func_type));
        unary_ind = false;
      } else if (expr[i++] == '(') {
        operators.emplace(LType::op, Lexem::braceOp);
        unary_ind = true;
      } else if (expr[i++] == ')') {
        while (!operators.empty() &&
               operators.top().getName() != Lexem::braceOp) {
          postfix_q_.push(operators.top());
          operators.pop();
        }
        if (!operators.empty() &&
            operators.top().getName() == Lexem::braceOp) {
          operators.pop();
        }
        unary_ind = false;
      } else {
        Lexem op = operators_.at(expr[i++]);
        while (!operators.empty() &&
               operators.top().getName() != Lexem::braceOp &&
               getPriority(operators.top().getName()) <= getPriority(op)) {
          if (op == Lexem::deg && operators.top().getName() == Lexem::deg) {
            break;
          }
          postfix_q_.push(operators.top());
          operators.pop();
        }
        operators.emplace(LType::op, op);
        unary_ind = true;
      }
    }
    while (!operators.empty()) {
      postfix_q_.push(operators.top());
      operators.pop();
    }
  }

  int getPriority(const Lexem &lexem) {
    try {
      return priorities_.at(lexem);
    } catch (const std::exception &e) {
      return -1;
    }
  }

  int detFunction(const std::string &expr, size_t &pos) const {
    if (pos + 4 < expr.length() && expr.substr(pos, pos + 5) == "log10") {
      pos += 5;
      return static_cast<int>(Lexem::log10);
    }
    for (const auto &function : functions_) {
      const std::string &func_str = function.first;
      if (pos + func_str.length() <= expr.length()) {
        if (expr.substr(pos, func_str.length()) == func_str) {
          pos += func_str.length();
          return static_cast<int>(function.second);
        }
      }
    }
    return 0;
  }

  void postfixCalc(std::string &expr) {
    std::stack<double> nums;
    bool is_number = false;
    while (!postfix_q_.empty()) {
      if (postfix_q_.front().getType() == LType::num) {
        nums.push(postfix_q_.front().getValue());
        postfix_q_.pop();
      } else if (postfix_q_.front().getType() == LType::func) {
        pushNumToStack(nums, calcFunctions(nums.top()));
      } else if (postfix_q_.front().getType() == LType::op) {
        double top_num = nums.top();
        if (postfix_q_.front().getName() == Lexem::unary) {
          pushNumToStack(nums, top_num * -1);
        } else if (nums.size() > 1) {
          nums.pop();
          double res = calcOperators(nums.top(), top_num, postfix_q_.front().getName());
          pushNumToStack(nums, res);
        }
      }
    }
    doubleToString(nums, expr);
  }

//      if (!is_number) {
//        double num_first = nums.top();
//        if (detFunction(postfix_q_.front())) {
//          pushNumToStack(nums, calcFunctions(num_first));
//        } else if (postfix_q_.front() == "~") {
//          num_first *= -1;
//          pushNumToStack(nums, num_first);
//        } else if (nums.size() > 1) {
//          nums.pop();
//          double value = nums.top();
//          value = calcOperators(value, num_first, postfix_q_.front());
//          pushNumToStack(nums, value);
//        }
//      }
//    }
//    doubleToString(nums, expr);
//  }

  void doubleToString(const std::stack<double> &nums, std::string &expr) {
    std::ostringstream stream;
    stream.precision(8);
    stream << std::fixed << nums.top();
    expr = stream.str();
    size_t iter = expr.find_last_not_of('0');
    if (expr[iter] == '.') {
      --iter;
    }
    expr = expr.substr(0, ++iter);
  }

  void pushNumToStack(std::stack<double> &nums, double value) {
    nums.pop();
    nums.push(value);
    postfix_q_.pop();
  }

  double calcFunctions(const double &num) {
    if (postfix_q_.front().getName() == Lexem::sqrt) {
      return std::sqrt(num);
    } else if (postfix_q_.front().getName() == Lexem::log) {
      return std::log(num);
    } else if (postfix_q_.front().getName() == Lexem::log10) {
      return std::log10(num);
    } else if (postfix_q_.front().getName() == Lexem::sin) {
      return std::sin(num);
    } else if (postfix_q_.front().getName() == Lexem::cos) {
      return std::cos(num);
    } else if (postfix_q_.front().getName() == Lexem::tan) {
      return std::tan(num);
    } else if (postfix_q_.front().getName() == Lexem::aSin) {
      return std::asin(num);
    } else if (postfix_q_.front().getName() == Lexem::aCos) {
      return std::acos(num);
    } else if (postfix_q_.front().getName() == Lexem::aTan) {
      return std::atan(num);
    } else {
      return 0;
    }
  }

  double calcOperators(const double &lhs, const double &rhs,
                       const Lexem &op) {
    if (op == Lexem::plus) {
      return lhs + rhs;
    } else if (op == Lexem::minus) {
      return lhs - rhs;
    } else if (op == Lexem::mul) {
      return lhs * rhs;
    } else if (op == Lexem::div) {
      return lhs / rhs;
    } else if (op == Lexem::mod) {
      return std::fmod(lhs, rhs);
    } else if (op == Lexem::deg) {
      return pow(lhs, rhs);
    } else {
      return 0;
    }
  }

  double extractDigit(const std::string &expr, size_t &i) {
    size_t start = i;
    while (i < expr.length() && (std::isdigit(expr[i]) || expr[i] == '.'))
         ++i;
    return std::stod(expr.substr(start, i - start));
  }

  void replace(std::string &expr, const std::string &old_s, const std::string &new_s) {
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

    if (parser.compile(expr, expression)) {
      return true;
    } else {
      expr = "Error";
      return false;
    }
  }
};
}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_
