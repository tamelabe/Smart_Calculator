#include <iostream>
#include "model.h"

int main() {
    std::string str = "sqrt(25)-1/2*sin((2^2)^2-2)";
    int i = 0;
    s21::Model model;
    model.infixToPrefix(str);
    std::cout << str << "\n";
    return 0;
};