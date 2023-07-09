#include "model.h"

s21::Model::Model() : expr_({}), expr_address(nullptr), x_expr_({}) {
  status_ = {0, "***Begin***\n-Init:      Success"};
  functions_ = {
      {"sin", Lexem::sin},   {"cos", Lexem::cos},   {"tan", Lexem::tan},
      {"asin", Lexem::aSin}, {"acos", Lexem::aCos}, {"atan", Lexem::aTan},
      {"sqrt", Lexem::sqrt}, {"log", Lexem::log},   {"log10", Lexem::log10}};
  operators_ = {
      {'^', Lexem::deg},     {'*', Lexem::mul},     {'/', Lexem::div},
      {'%', Lexem::mod},     {'+', Lexem::plus},    {'-', Lexem::minus},
      {')', Lexem::braceCl}, {'(', Lexem::braceOp}, {'~', Lexem::unary}};
  priorities_ = {{Lexem::sin, 0},     {Lexem::cos, 0},     {Lexem::tan, 0},
                 {Lexem::aSin, 0},    {Lexem::aCos, 0},    {Lexem::aTan, 0},
                 {Lexem::sqrt, 0},    {Lexem::log, 0},     {Lexem::log10, 0},
                 {Lexem::braceOp, 1}, {Lexem::braceCl, 2}, {Lexem::deg, 3},
                 {Lexem::mul, 4},     {Lexem::div, 4},     {Lexem::mod, 4},
                 {Lexem::plus, 5},    {Lexem::minus, 5},   {Lexem::unary, 5}};
}

void s21::Model::setExpr(std::string &expr, std::string &x_expr) {
  if (expr.empty()) {
    status_ = {10, "-Set:      Fail (empty string)"};
    return;
  }
  expr_ = expr;
  expr_address = &expr;
  status_ = {11, "-Set:       Success (main string)"};
  if (!x_expr.empty()) {
    x_expr_ = x_expr;
    status_ = {12, "-Set:       Success (main and x strings)"};
  }
}

void s21::Model::prepareExpr() {
  if (status_.first % 10 == 0) return;
  if (status_.first == 12) replace("x", x_expr_);
  expr_.erase(std::remove(expr_.begin(), expr_.end(), ' '), expr_.end());
  replace("log", "log10");
  replace("ln", "log");
  replace("mod", "%");
  status_ = {21, "-Prepare:   Success"};
}

void s21::Model::validateExpr() {
  if (status_.first % 10 == 0) return;
  exprtk::symbol_table<double> symbol_table;
  exprtk::expression<double> expression;
  exprtk::parser<double> parser;
  symbol_table.add_constants();
  expression.register_symbol_table(symbol_table);
  if (parser.compile(expr_, expression)) {
    status_ = {22, "-Validate:  Success"};
  } else {
    status_ = {20, "-Validate:  Fail"};
  }
}

void s21::Model::calculateExpr() {
  if (status_.first % 10 == 0) return;
  infixToPostfix();
  postfixCalc();
  if (status_.first % 10 != 0) {
    if (expr_ == "inf") {
      status_ = {30, "-Calculate: Fail (infinity)"};
    } else if (expr_ == "nan") {
      status_ = {30, "-Calculate: Fail (NaN)"};
    } else {
      status_ = {31, "-Calculate: Success"};
    }
  }
}

void s21::Model::replaceStr() {
  if (status_.first % 10 == 0) {
    *expr_address = "Error";
    return;
  }
    *expr_address = expr_;
    status_ = {41, "-Replace:   Success\n***Finish!***"};
}

void s21::Model::infixToPostfix() {
  std::unordered_map<Lexem, std::string> dec_map;
  std::stack<Token> operators;
  bool unary_ind = true;
  size_t expr_length = expr_.length();
  for (size_t i = 0; i < expr_length && status_.first != 40;) {
    if (unary_ind && (expr_[i] == '-' || expr_[i] == '+')) {
      if (expr_[i] == '-') operators.emplace(LType::op, Lexem::unary);
      ++i;
    } else if (std::isdigit(expr_[i]) || expr_[i] == '.' || expr_[i] == 'e') {
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
  while (!operators.empty()) {
    stackToQueue(operators);
  }
}

s21::Model::Lexem s21::Model::charToLexem(const char &oper) {
  Lexem lex = Lexem::braceOp;
  try {
    lex = operators_.at(oper);
  } catch (const std::out_of_range &e) {
    status_ = {30, "-Calculate: Fail (unknown lexem)"};
    lex = Lexem::braceOp;
    return lex;
  }
  return lex;
}

void s21::Model::stackToQueue(std::stack<Token> &operators) {
  postfix_q_.push(operators.top());
  operators.pop();
}

int s21::Model::getPriority(const Lexem &lexem) {
  int priority = -1;
  try {
    priority = priorities_.at(lexem);
  } catch (const std::exception &e) {
    status_ = {30, "-Calculate: Fail (priority error)"};
  }
  return priority;
}

int s21::Model::detFunction(const std::string &expr, size_t &pos) const {
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

void s21::Model::postfixCalc() {
  if (status_.first % 10 == 0) return;
  std::stack<double> nums;
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
        double res =
            calcOperators(nums.top(), top_num, postfix_q_.front().getName());
        pushNumToStack(nums, res);
      }
    }
  }
  doubleToString(nums.top());
}

void s21::Model::doubleToString(const double &num) {
  std::ostringstream stream;
  stream.precision(8);
  stream << std::fixed << num;
  expr_ = stream.str();
  size_t iter = expr_.find_last_not_of('0');
  if (expr_[iter] == '.') --iter;
  expr_ = expr_.substr(0, ++iter);
}

void s21::Model::pushNumToStack(std::stack<double> &nums, double value) {
  nums.pop();
  nums.push(value);
  postfix_q_.pop();
}

double s21::Model::calcFunctions(const double &num) {
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

double s21::Model::calcOperators(const double &lhs, const double &rhs,
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

double s21::Model::extractDigit(const std::string &expr, size_t &i) {
  size_t start = i;
  while (i < expr.length() && (std::isdigit(expr[i]) || expr[i] == '.')) ++i;
  return std::stod(expr.substr(start, i - start));
}

void s21::Model::replace(const std::string &old_s, const std::string &new_s) {
  size_t pos = expr_.find(old_s);
  while (pos != std::string::npos) {
    expr_.replace(pos, old_s.length(), new_s);
    pos = expr_.find(old_s, pos + 1);
  }
}
