#ifndef SRC_MODEL_MAIN_MODEL_H_
#define SRC_MODEL_MAIN_MODEL_H_

#include <cmath>
#include <queue>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <map>
#include <iostream>

#include "../resources/exprtk.hpp"

namespace s21 {
class Model {
  class Token;
  enum class Lexem;
  enum class LType;

 public:
  Model();

  /**
   * @brief Accessor of calculation state parameter
   * @return std::pair - status code[int] | message[std::string]
   */
  std::pair<int, std::string> getStatus() { return status_; }
  /**
    * @brief Accessor of calculation result
    * @return result
    */
  std::string getResult() { return expr_; }
  double getResultD() { return result_; }
  void setExpr(const std::string &expr);
  void setXValue(const std::string &x_value);
  void setXValue(const double &x_value);
  void validateExpr();
  void convertExpr();
  void calculateExpr();

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
    num,
    num_x
  };
  enum class LType : int { num, func, op };
  /**
   * Nested class with data for each calculation lexem
   */
  class Token {
   public:
    Token(LType type, Lexem name) : type_(type), name_(name), value_{} {}
    Token(LType type, Lexem name, double value)
        : type_(type), name_(name), value_(value) {}
    LType getType() const { return type_; }
    Lexem getName() const { return name_; }
    double getValue() const { return value_; }


   private:
    LType type_{};
    Lexem name_{};
    double value_{};
  };

  std::string expr_{};
  double x_value_{};
  double result_{};

  std::pair<int, std::string> status_;

  std::unordered_map<std::string, Lexem> functions_;
  std::unordered_map<char, Lexem> operators_;
  std::unordered_map<Lexem, int> priorities_;
  std::queue<Token> postfix_q_{};

  void substituteExpr();
  Lexem charToLexem(const char &oper);
  void stackToQueue(std::stack<Token> &operators);
  int getPriority(const Lexem &lexem);
  int detFunction(size_t &pos) const;
  void postfixCalc();
  void doubleToString();
  void stringOutput();
  void pushNumToStack(std::stack<double> &nums, double value);
  double calcFunctions(const double &num);
  double calcOperators(const double &lhs, const double &rhs, const Lexem &op);
  double extractDigit(size_t &pos);
  void replace(const std::string &old_s, const std::string &new_s);
  bool errCheck();
};
}  // namespace s21

#endif  // SRC_MODEL_MAIN_MODEL_H_
