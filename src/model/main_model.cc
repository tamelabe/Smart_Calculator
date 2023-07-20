#include "main_model.h"

#include <iostream>

s21::MainModel::MainModel() {
  status_ = {0, "***Begin***\n-Init:      Success"};
  mapsObjectsInit();
}

/**
 * @brief Expression setter (mutator)
 * @param expr - main expression
 * @param x_expr - X field expression
 */
void s21::MainModel::setExpr(const std::string &expr) {
  expr_ = expr;
  postfix_v_.clear();
  status_ = {11, "-Set:       Success (main string)"};
  if (x_value_ != 0) {
    status_ = {12, "-Set:       Success (main string and x value - str)"};
  }
}

/**
 * @brief Sets X value param
 * @param x_value - input string
 */
void s21::MainModel::setXValue(const std::string &x_value) {
  if (x_value.empty()) {
    x_status_ = false;
    return;
  }
  try {
    x_value_ = std::stod(x_value);
    x_status_ = true;
  } catch (const std::exception &e) {
    status_ = {10, "-Set:       Fail (x value is not a number)"};
    x_status_ = false;
    return;
  }
  if (expr_.empty()) {
    status_ = {10, "-Set:       In progress... (x value - str)"};
  } else {
    status_ = {12, "-Set:       Success (main string and x value - str)"};
  }
}

/**
 * @brief Sets X value param
 * @param x_value - input double number
 */
void s21::MainModel::setXValue(const double &x_value) {
  if (expr_.empty()) {
    status_ = {10, "-Set:       In progress... (x value - str)"};
  } else {
    status_ = {12, "-Set:       Success (main string and x value - str)"};
  }
  x_value_ = x_value;
  x_status_ = true;
}

/**
 * @brief Expression preparer:
 *  - replaces 'x' chars with an x field expression
 *  - substitutes "log", "ln" functions and "mod" operator to validator
 * understandable names
 */
void s21::MainModel::substituteExpr() {
  expr_.erase(std::remove(expr_.begin(), expr_.end(), ' '), expr_.end());
  replace("log", "log10");
  replace("ln", "log");
  replace("mod", "%");
  replace("e", "*10^");
  status_ = {21, "-Substitute: Success"};
}

/**
 * @brief Expression validator based on exprtk library
 */
void s21::MainModel::validateExpr() {
  if (errCheck()) return;
  substituteExpr();
  exprtk::symbol_table<double> symbol_table;
  exprtk::expression<double> expression;
  exprtk::parser<double> parser;
  symbol_table.add_constants();
  double x;
  symbol_table.add_variable("x", x);
  expression.register_symbol_table(symbol_table);
  if (parser.compile(expr_, expression)) {
    status_ = {22, "-Validate:  Success"};
  } else {
    status_ = {20, "-Validate:  Fail"};
  }
}

/**
 * @brief Expression calculator. Based on method of translation and further
 * calculation of the postfix notation
 */
void s21::MainModel::calculateExpr() {
  if (!postfix_v_.empty()) {
    postfixCalc();
  } else {
    status_ = {30, "-Conversion: Fail (empty token queue)"};
  }
  stringOutput();
}

/**
 * @brief Infix to postfix notation converter. Based on shunting yard algorithm
 */
void s21::MainModel::convertExpr() {
  if (errCheck()) return;
  std::unordered_map<Lexem, std::string> dec_map;
  std::stack<Token> operators;
  bool unary_ind = true;
  size_t expr_length = expr_.length(), i = 0;
  while (i < expr_length && status_.first != 40) {
    if (unary_ind && (expr_[i] == '-' || expr_[i] == '+')) {
      if (expr_[i] == '-') operators.emplace(LType::op, Lexem::unary);
      ++i;
    } else if (std::isdigit(expr_[i]) || expr_[i] == '.') {
      postfix_v_.emplace_back(LType::num, Lexem::num, extractDigit(i));
      unary_ind = false;
    } else if (expr_[i] == 'x') {
      postfix_v_.emplace_back(LType::num, Lexem::num_x);
      unary_ind = false;
      ++i;
    } else if (int func_type = detFunction(i)) {
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
        stackToQueue(operators);
      }
      if (!operators.empty() && operators.top().getName() == Lexem::braceOp)
        operators.pop();
      unary_ind = false;
    } else {
      Lexem op = charToLexem(expr_[i++]);
      while (!operators.empty() &&
             operators.top().getName() != Lexem::braceOp &&
             getPriority(operators.top().getName()) <= getPriority(op)) {
        if (op == Lexem::deg && operators.top().getName() == Lexem::deg) break;
        stackToQueue(operators);
      }
      operators.emplace(LType::op, op);
      unary_ind = true;
    }
  }
  while (!operators.empty()) stackToQueue(operators);
}

/**
 * @brief Postfix notation calculator. Works with stack of tokens
 */
void s21::MainModel::postfixCalc() {
  if (errCheck()) return;
  std::stack<double> nums;
  for (size_t pos = 0; pos < postfix_v_.size() && !errCheck(); ++pos) {
    if (postfix_v_[pos].getType() == LType::num) {
      if (postfix_v_[pos].getName() == Lexem::num_x) {
        if (!x_status_) status_ = {50, "Calculation: Fail (x is not set)"};
        nums.push(x_value_);
      } else {
        nums.push(postfix_v_[pos].getValue());
      }
    } else if (postfix_v_[pos].getType() == LType::func) {
      pushNumToStack(nums,
                     calcFunctions(nums.top(), postfix_v_[pos].getName()));
    } else if (postfix_v_[pos].getType() == LType::op) {
      double top_num = nums.top();
      if (postfix_v_[pos].getName() == Lexem::unary) {
        pushNumToStack(nums, top_num * -1);
      } else if (nums.size() > 1) {
        nums.pop();
        double res =
            calcOperators(nums.top(), top_num, postfix_v_[pos].getName());
        pushNumToStack(nums, res);
      }
    }
  }
  if (nums.size() == 1) {
    result_ = nums.top();
  } else {
    status_ = {50, "Calculation: Fail"};
  }
}

/**
 * @brief Assigns result to original string
 */
void s21::MainModel::stringOutput() {
  if (errCheck()) {
    expr_ = "Error";
    return;
  }
  doubleToString();
  if (expr_ == "inf") {
    status_ = {40, "-Calculate: Fail (infinity)"};
    expr_ = "Error";
    result_ = 0;
  } else if (expr_ == "nan") {
    status_ = {40, "-Calculate: Fail (NaN)"};
    expr_ = "Error";
    result_ = 0;
  } else {
    status_ = {41, "-Calculate: Success\n***Finish!***"};
  }
}

/**
 * @brief Calculates an arrays of coordinates for plotting in QCustomPlot
 * @param XS - Lower X board on the graph
 * @param XF - Upper X board on the graph
 * @param YS - Lower Y board on the graph
 * @param YF - Upper Y board on the graph
 * @return - pair of X and Y vectors
 */
std::pair<std::vector<double>, std::vector<double>> s21::MainModel::getGraphVector(
    const double &XS, const double &XF, const double &YS, const double &YF) {
  // Initialization to avoid duplication
  std::vector<double> XVector;
  std::vector<double> YVector;
  double x_delta = XF - XS;
  double y_delta = YF - YS;
  // Error processing
  if (errCheck()) {
    return {XVector, YVector};
  } else if (x_delta <= 0 || y_delta <= 0) {
    status_ = {70, "Graph: Fail (invalid axis range)"};
    return {XVector, YVector};
  }
  // Equal points distribution method
  double acc = x_delta / 340, dist = 0;
  double x_curr = XS, y_curr = 0, x_prev = XS - acc, y_prev = YS;
  while (x_curr <= XF) {
    y_curr = graphYCalculation(x_curr, x_curr, acc);
    if (y_curr != 0 && y_curr >= YS && y_curr <= YF) {
      dist = std::sqrt(std::pow((340 * (x_curr - x_prev) / x_delta), 2) +
                       std::pow((190 * (y_curr - y_prev) / y_delta), 2));
      while ((dist > 2.7 && dist < 100 && acc > 1e-10) || dist < 2.6) {
        if (dist > 2.7) {
          acc /= 1.01;
        } else {
          acc *= 1.01;
        }
        y_curr = graphYCalculation(x_curr, x_prev, acc);
        dist = std::sqrt(std::pow((340 * (x_curr - x_prev) / x_delta), 2) +
                         std::pow((190 * (y_curr - y_prev) / y_delta), 2));
      }
      x_prev = x_curr;
      y_prev = y_curr;
      XVector.push_back(x_curr);
      YVector.push_back(y_curr);
    }
  }
  return {XVector, YVector};
}

/**
 * @brief Сalculates the y coordinate and offsets x by the given accuracy
 * @param x_curr - current X value
 * @param x_prev - previous X value
 * @param acc - accuracy
 * @return - new Y coordinate
 */
double s21::MainModel::graphYCalculation(double &x_curr, const double &x_prev,
                                     const double &acc) {
  x_curr = x_prev + acc;
  setXValue(x_curr);
  calculateExpr();
  status_ = {81, "Graph: Calculated"};
  return getResultD();
}

/**
 * @brief Operator to enum converter (Lexem class element)
 * @param oper - char operator
 * @return enum class operator
 */
s21::MainModel::Lexem s21::MainModel::charToLexem(const char &oper) {
  Lexem lex;
  try {
    lex = operators_.at(oper);
  } catch (const std::out_of_range &e) {
    status_ = {30, "-Calculate: Fail (unknown lexem)"};
    lex = Lexem::braceOp;
    return lex;
  }
  return lex;
}

/**
 * @brief Stack to queue transition method
 * @param operators stack of operators
 */
void s21::MainModel::stackToQueue(std::stack<Token> &operators) {
  postfix_v_.push_back(operators.top());
  operators.pop();
}

/**
 * @brief Priorities of the Lexem determinant
 * @param lexem - enum class member
 * @return math expression priority
 */
int s21::MainModel::getPriority(const Lexem &lexem) {
  return priorities_.at(lexem);
}

/**
 * @brief Function finder. Starts from a given position.
 * Adds the number of characters to the position variable
 * @param pos - start string position
 * @return if function exists: function length, else 0
 */
int s21::MainModel::detFunction(size_t &pos) const {
  if (pos + 4 < expr_.length() && expr_.substr(pos, pos + 5) == "log10") {
    pos += 5;
    return static_cast<int>(Lexem::log10);
  }
  for (const auto &function : functions_) {
    const std::string &func_str = function.first;
    if (pos + func_str.length() <= expr_.length()) {
      if (expr_.substr(pos, func_str.length()) == func_str) {
        pos += func_str.length();
        return static_cast<int>(function.second);
      }
    }
  }
  return 0;
}

/**
 * @brief Double to std::string converter with the specified accuracy
 */
void s21::MainModel::doubleToString() {
  std::ostringstream stream;
  stream.precision(8);
  stream << std::fixed << result_;
  expr_ = stream.str();
  size_t iter = expr_.find_last_not_of('0');
  if (expr_[iter] == '.') --iter;
  expr_ = expr_.substr(0, ++iter);
}

/**
 * @brief Pushes number to calculation stack
 * @param nums - calculation numbers stack
 * @param value - number to push
 */
void s21::MainModel::pushNumToStack(std::stack<double> &nums, double value) {
  nums.pop();
  nums.push(value);
}

/**
 * @brief Functions calculator.
 * @param num - function parameter
 * @return result
 */
double s21::MainModel::calcFunctions(const double &num, Lexem function) {
  if (function == Lexem::sqrt) {
    return std::sqrt(num);
  } else if (function == Lexem::log) {
    return std::log(num);
  } else if (function == Lexem::log10) {
    return std::log10(num);
  } else if (function == Lexem::sin) {
    return std::sin(num);
  } else if (function == Lexem::cos) {
    return std::cos(num);
  } else if (function == Lexem::tan) {
    return std::tan(num);
  } else if (function == Lexem::aSin) {
    return std::asin(num);
  } else if (function == Lexem::aCos) {
    return std::acos(num);
  } else {
    return std::atan(num);
  }
}

/**
 * @brief Operators calculator
 * @param lhs - left hand side number
 * @param rhs - right hand side number
 * @param op - operator
 * @return result
 */
double s21::MainModel::calcOperators(const double &lhs, const double &rhs,
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
  } else {  // (op == Lexem::deg)
    return std::pow(lhs, rhs);
  }
}

/**
 * @brief Digit extractor from std::string
 * @param pos - string postition
 * @return result
 */
double s21::MainModel::extractDigit(size_t &pos) {
  size_t start = pos;
  while (pos < expr_.length() &&
         (std::isdigit(expr_[pos]) || expr_[pos] == '.'))
    ++pos;
  return std::stod(expr_.substr(start, pos - start));
}

/**
 * @brief Replaces all occurrences of substring
 * @param old_s - exist substring
 * @param new_s - new substring
 */
void s21::MainModel::replace(const std::string &old_s, const std::string &new_s) {
  size_t pos = expr_.find(old_s);
  while (pos != std::string::npos) {
    expr_.replace(pos, old_s.length(), new_s);
    pos = expr_.find(old_s, pos + 1);
  }
}

bool s21::MainModel::errCheck() { return status_.first % 10 == 0; }

/**
 * @brief Initialize function, operators and priorities unordered maps
 */
void s21::MainModel::mapsObjectsInit() {
  functions_ = {
      {"sin", Lexem::sin},   {"cos", Lexem::cos},   {"tan", Lexem::tan},
      {"asin", Lexem::aSin}, {"acos", Lexem::aCos}, {"atan", Lexem::aTan},
      {"sqrt", Lexem::sqrt}, {"log", Lexem::log},   {"log10", Lexem::log10}};
  operators_ = {
      {'^', Lexem::deg}, {'*', Lexem::mul},  {'/', Lexem::div},
                {'%', Lexem::mod}, {'+', Lexem::plus}, {'-', Lexem::minus}};
  priorities_ = {{Lexem::sin, 0},   {Lexem::cos, 0},  {Lexem::tan, 0},
                 {Lexem::aSin, 0},  {Lexem::aCos, 0}, {Lexem::aTan, 0},
                 {Lexem::sqrt, 0},  {Lexem::log, 0},  {Lexem::log10, 0},
                 {Lexem::unary, 2}, {Lexem::deg, 3},  {Lexem::mul, 4},
                 {Lexem::div, 4},   {Lexem::mod, 4},  {Lexem::plus, 5},
                 {Lexem::minus, 5}};
}
