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
  enum class Lexem;
  enum class LType;
  class Token;

 public:
  Model() : expr_({}), expr_address(nullptr), x_expr_({}), x_expr_address(nullptr) {
    status_ = {0, "***Begin***\n-Init:      Success"};
    functions_ = {
        {"sin", Lexem::sin},   {"cos", Lexem::cos},   {"tan", Lexem::tan},
        {"asin", Lexem::aSin}, {"acos", Lexem::aCos}, {"atan", Lexem::aTan},
        {"sqrt", Lexem::sqrt}, {"log", Lexem::log},   {"log10", Lexem::log10}};
    operators_ = {
        {'^', Lexem::deg}, {'*', Lexem::mul},  {'/', Lexem::div},
        {'%', Lexem::mod}, {'+', Lexem::plus}, {'-', Lexem::minus}};
    priorities_ = {
        {Lexem::sin, 0},     {Lexem::cos, 0},     {Lexem::tan, 0},
        {Lexem::aSin, 0},    {Lexem::aCos, 0},    {Lexem::aTan, 0},
        {Lexem::sqrt, 0},    {Lexem::log, 0},     {Lexem::log10, 0},
        {Lexem::braceOp, 1}, {Lexem::braceCl, 1}, {Lexem::deg, 2},
        {Lexem::mul, 4},     {Lexem::div, 4},     {Lexem::mod, 4},
        {Lexem::plus, 5},    {Lexem::minus, 5},   {Lexem::unary, 5}};
  }

  std::pair<int, std::string> getStatus() {
    return status_;
  };

  void setExpr(std::string &expr, std::string &x_expr) {
    if (expr.empty()) {
      status_ = {10, "-Set:      Fail (empty string)"};
      return;
    }
    expr_ = expr;
    expr_address = &expr;
    status_ = {11, "-Set:       Success (main string)"};
    if (!x_expr.empty()) {
      x_expr_ = x_expr;
      x_expr_address = &x_expr;
      status_ = {12, "-Set:       Success (main and x strings)"};
    }
  }

  void prepareExpr() {
    if (status_.first % 10 == 0) { return; }
    if (status_.first == 12)
      replace("x", x_expr_);
    replace("log", "log10");
    replace("ln", "log");
    replace("mod", "%");
    status_ = {21, "-Prepare:   Success"};
  }

  void validateExpr() {
    if (status_.first % 10 == 0) { return; }
    exprtk::symbol_table<double> symbol_table;
    exprtk::expression<double> expression;
    exprtk::parser<double> parser;

    symbol_table.add_constants();
    expression.register_symbol_table(symbol_table);
    expr_.erase(std::remove(expr_.begin(), expr_.end(), ' '), expr_.end());

    if (parser.compile(expr_, expression)) {
      status_ = {22, "-Validate:  Success"};
    } else {
      status_ = {20, "-Validate:  Fail"};
    }
  }

  void calculateExpr() {
    if (status_.first % 10 == 0) { return; }
    infixToPostfix();
    postfixCalc();
    if (status_.first % 10 != 0) {
      status_ = {31, "-Calculate: Success"};
    }
  }

  void replaceStr() {
    if (status_.first % 10 == 0) {
      *expr_address = "Error";
    } else {
      *expr_address = expr_;
      status_ = {41, "-Replace:   Success\n***Finish!***"};
    }
  }

 private:
  std::pair<int, std::string> status_;

  std::string expr_;
  std::string x_expr_;

  std::string* expr_address;
  std::string* x_expr_address;

  std::unordered_map<std::string, Lexem> functions_;
  std::unordered_map<char, Lexem> operators_;
  std::unordered_map<Lexem, int> priorities_;
  std::queue<Token> postfix_q_;

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
    [[nodiscard]] LType getType() const { return type_; }
    [[nodiscard]] Lexem getName() const { return name_; }
    [[nodiscard]] double getValue() const { return value_; }
   private:
    LType type_;
    Lexem name_;
    double value_;
  };

  void infixToPostfix() {
    std::stack<Token> operators;
    bool unary_ind = true;
    for (size_t i = 0; i < expr_.length();) {
      if (unary_ind && (expr_[i] == '-' || expr_[i] == '+')) {
        if (expr_[i] == '-') operators.emplace(LType::op, Lexem::unary);
        ++i;
      }
      if (std::isdigit(expr_[i]) || expr_[i] == '.' || expr_[i] == 'e') {
        postfix_q_.emplace(LType::num, Lexem::num, extractDigit(expr_, i));
        unary_ind = false;
      } else if (int func_type = detFunction(expr_, i)) {
        operators.emplace(LType::func, static_cast<Lexem>(func_type));
        unary_ind = false;
      } else if (expr_[i] == '(') {
        operators.emplace(LType::op, Lexem::braceOp);
        unary_ind = true;
        ++i;
      } else if (expr_[i] == ')') {
        ++i;
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
        Lexem op = operators_.at(expr_[i++]);
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

  void postfixCalc() {
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
    doubleToString(nums);
  }

  void doubleToString(const std::stack<double> &nums) {
    std::ostringstream stream;
    stream.precision(8);
    stream << std::fixed << nums.top();
    expr_ = stream.str();
    size_t iter = expr_.find_last_not_of('0');
    if (expr_[iter] == '.') {
      --iter;
    }
    expr_ = expr_.substr(0, ++iter);
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

  void replace(const std::string &old_s, const std::string &new_s) {
    size_t pos = expr_.find(old_s);
    while (pos != std::string::npos) {
      expr_.replace(pos, old_s.length(), new_s);
      pos = expr_.find(old_s, pos + 1);
    }
  }

};
}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_
