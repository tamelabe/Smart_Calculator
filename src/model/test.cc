#include <iostream>

#include "model.h"

int main() {
  std::string str = "1+1";
  int i = 0;
  s21::Model model;
  //    model.infixToPostfix(str);
  model.calculate(str, str);
  std::cout << str << "\n";
  return 0;
};