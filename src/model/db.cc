#include "main_model.h"
#include <iostream>

int main() {
  s21::Model a;
  a.setExpr("((sin(2.3) * (sqrt(7.8) + cos(1.2))) mod 4.5) / (log(5.6) + atan(0.9))", "");
  a.prepareExpr();
//  a.validateExpr();
  a.calculateExpr();
  std::cout << a.getResultS() << '\n';


  return 0;
}