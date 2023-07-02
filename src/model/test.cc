#include <iostream>

#include "model.h"

int main() {
  std::string str = "(132+sin(asin(sqrt(ln(log(228.11)))))-4*5^6*(123))";
  int i = 0;
  s21::Model model;
  //    model.infixToPostfix(str);
  model.calculate(str, str);
  std::cout << str << "\n";
  return 0;
};