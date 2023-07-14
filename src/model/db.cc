#include <iostream>

#include "main_model.h"

int main() {
  s21::Model calc_;
  calc_.setExpr("log(4)");
  //    std::cout << calc_.getStatus().second << '\n';
  calc_.validateExpr();
  //    std::cout << calc_.getStatus().second << '\n';
  calc_.convertExpr();
  //    std::cout << calc_.getStatus().second << '\n';
  calc_.calculateExpr();
  //  std::cout << calc_.getResult() << '\n';

  return 0;
}