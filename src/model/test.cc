#include <iostream>

#include "model.h"

int main() {
  std::string str = "sin(1)+cos(1)+asin(1)+acos(1)+atan(1)+tan(1)+sqrt(16)+ln(10)+log(10)";
  int i = 0;
  s21::Model model;
  //    model.infixToPostfix(str);
  model.calculate(str, str);
  std::cout << str << "\n";
  return 0;
};