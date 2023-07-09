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
  Model();

  std::pair<int, std::string> getStatus() { return status_; };
  void setExpr(std::string &expr, std::string &x_expr);
  void prepareExpr();
  void validateExpr();
  void calculateExpr();
  void replaceStr();

 private:
  std::pair<int, std::string> status_;

  std::string expr_;
  std::string x_expr_;
  std::string *expr_address;

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
  enum class LType : int { num, func, op };
  class Token {
   public:
    Token(LType type, Lexem name) : name_(name), type_(type), value_{} {}
    Token(LType type, Lexem name, double value)
        : name_(name), type_(type), value_(value) {}
    [[nodiscard]] LType getType() const { return type_; }
    [[nodiscard]] Lexem getName() const { return name_; }
    [[nodiscard]] double getValue() const { return value_; }

   private:
    LType type_;
    Lexem name_;
    double value_;
  };

  void infixToPostfix();
  Lexem charToLexem(const char &oper);
  void stackToQueue(std::stack<Token> &operators);
  int getPriority(const Lexem &lexem);
  int detFunction(const std::string &expr, size_t &pos) const;
  void postfixCalc();
  void doubleToString(const double &num);
  void pushNumToStack(std::stack<double> &nums, double value);
  double calcFunctions(const double &num);
  double calcOperators(const double &lhs, const double &rhs, const Lexem &op);
  double extractDigit(const std::string &expr, size_t &i);
  void replace(const std::string &old_s, const std::string &new_s);
};
}  // namespace s21

#endif  // SRC_MODEL_MODEL_H_
