#include "main_model.h"
#include <iostream>

int main() {
  s21::Model a;
  a.setExpr("10^-2 * 1000", "");
  a.prepareExpr();
  a.validateExpr();
  a.calculateExpr();
  std::cout << a.getResultS() << '\n';


  return 0;
}