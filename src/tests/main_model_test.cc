#include <gtest/gtest.h>

#include "../model/main_model.h"

using namespace s21;

class MainCalc : public testing::Test {
 protected:
  void calculate(std::string &expr) {
    calc_.setExpr(expr);
//    std::cout << calc_.getStatus().second << '\n';
    calc_.validateExpr();
//    std::cout << calc_.getStatus().second << '\n';
    calc_.convertExpr();
//    std::cout << calc_.getStatus().second << '\n';
    calc_.calculateExpr();
//    std::cout << calc_.getStatus().second << '\n';
  }

  Model calc_;

  std::string error_ = "Error";

  std::string err_div_zero_ = "1/0";
  std::string err_sqrt_oppos_ = "sqrt(-1)";
  std::string err_abracadabra_ = "1234g43s;;";
  std::string err_empty_ = "";
  std::string fail_lexem_ = "1;02941257";
  std::string fail_x_lexem_ = "qwerty";
  std::string fail_x_lexem_expr_ = "sin(x)";

  std::string simple_log_ = "log(4)";
  std::string simple_log_res_ = "0.60205999";
  std::string multifold_ = "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  std::string multifold_res_ = "-30.07216495";
  std::string functions_t_ = "sin(1)+cos(1)+asin(1)+acos(1)+atan(1)+tan(1)+sqrt(16)+ln(10)+log(10)";
  std::string functions_res_ = "12.5979606";
  std::string folded_funcs_ = "(132+sin(asin(sqrt(ln(log(228.11)))))-4*5^6*(123))";
  std::string folded_funcs_res_ = "-7687367.07378458";
  std::string exp_notation_ = "2.5 * 10^3 + 1.8 * 10^-2 * (3.7e-5 + 2.1e2)";
  std::string exp_notation_res_ = "2503.78000067";
  std::string exp_not_simple_ = "1.5e5";
  std::string exp_not_simple_res_ = "150000";
  std::string degree_hard_ = "2^3^4";
  std::string degree_hard_res_ = "2417851639229258349412352";
  std::string degree_funcs = "sin(.2)^(cos(1)+tan(1.1))^sin(.6)";
  std::string degree_funcs_res = "0.06624972";
  std::string x_str_main_ = "sqrt((7.2 + 3.5 - 2.8) / (5.6 * 4.2)) + sin(x) - cos(1.3)";
  std::string x_str_ = "0.8";
  double x_str_d_ = 0.8;
  std::string x_str_res_ = "1.02941257";
  std::string mod_ = "((sin(2.3) * (sqrt(7.8) + cos(1.2))) mod 4.5) / (log(5.6) + atan(0.9))";
  std::string mod_res_ = "1.588689";
  std::string graph_func_ = "x^2";
  double x_begin_ = -30;
  double y_begin_ = -30;
  double x_end_ = 30;
  double y_end_ = 900;
  std::pair<std::vector<double>, std::vector<double>> vector_;
  std::vector<double> XVector, YVector;
};

TEST_F(MainCalc, DivByZero) {
  calculate(err_div_zero_);
  EXPECT_EQ(calc_.getResult(), error_);
}

TEST_F(MainCalc, sqrtOpp) {
  calculate(err_sqrt_oppos_);
  EXPECT_EQ(calc_.getResult(), error_);
}

TEST_F(MainCalc, invExpr) {
  calculate(err_abracadabra_);
  EXPECT_EQ(calc_.getResult(), error_);
}

TEST_F(MainCalc, SimpleLog) {
  calculate(simple_log_);
  EXPECT_EQ(calc_.getResult(), simple_log_res_);
}

TEST_F(MainCalc, Multifold) {
  calculate(multifold_);
  EXPECT_EQ(calc_.getResult(), multifold_res_);
}

TEST_F(MainCalc, Functions) {
  calculate(functions_t_);
  EXPECT_EQ(calc_.getResult(), functions_res_);
}

TEST_F(MainCalc, Folded_funcs) {
  calculate(folded_funcs_);
  EXPECT_EQ(calc_.getResult(), folded_funcs_res_);
}

TEST_F(MainCalc, Exp_notation) {
  calculate(exp_notation_);
  EXPECT_EQ(calc_.getResult(), exp_notation_res_);
}

TEST_F(MainCalc, expNSimple) {
  calculate(exp_not_simple_);
  EXPECT_EQ(calc_.getResult(), exp_not_simple_res_);
}

TEST_F(MainCalc, degreeHard) {
  calculate(degree_hard_);
  EXPECT_EQ(calc_.getResult(), degree_hard_res_);
}

TEST_F(MainCalc, degreeFuncs) {
  calculate(degree_funcs);
  EXPECT_EQ(calc_.getResult(), degree_funcs_res);
}

TEST_F(MainCalc, xStrEnable) {
  calc_.setXValue(x_str_);
  calculate(x_str_main_);
  EXPECT_EQ(calc_.getResult(), x_str_res_);
}

TEST_F(MainCalc, xStrEnableDouble) {
  calc_.setXValue(x_str_d_);
  calculate(x_str_main_);
  EXPECT_EQ(calc_.getResult(), x_str_res_);
}

TEST_F(MainCalc, xStrEnableDoubleAfter) {
  calc_.setExpr(fail_x_lexem_expr_);
  calc_.setXValue("0.8");
  calc_.validateExpr();
  calc_.convertExpr();
  calc_.calculateExpr();
  EXPECT_EQ(calc_.getResultD(), std::sin(0.8));
}

TEST_F(MainCalc, modTest) {
  calculate(mod_);
  EXPECT_EQ(calc_.getResult(), mod_res_);
}

TEST_F(MainCalc, failUnknownLex) {
  calc_.setExpr(fail_lexem_);
  calc_.convertExpr();
  calc_.calculateExpr();
  EXPECT_EQ(calc_.getStatus().first, 30);
  EXPECT_EQ(calc_.getResult(), error_);
}

TEST_F(MainCalc, failXValue) {
  calc_.setExpr(fail_x_lexem_expr_);
  calc_.validateExpr();
  calc_.convertExpr();
  calc_.setXValue(fail_x_lexem_);
  calc_.calculateExpr();
  EXPECT_EQ(calc_.getStatus().first, 10);
  EXPECT_EQ(calc_.getResult(), error_);
}

TEST_F(MainCalc, graphTest) {
  calc_.setExpr(graph_func_);
  calc_.validateExpr();
  calc_.convertExpr();
  vector_ = calc_.getGraphVector(x_begin_, x_end_, y_begin_, y_end_);
  XVector = vector_.first;
  YVector = vector_.second;
  EXPECT_EQ(XVector.back(), 30);
  EXPECT_EQ(YVector.back(), 900);
}

TEST_F(MainCalc, graphTestFail) {
  vector_ = calc_.getGraphVector(x_begin_, x_end_, y_begin_, y_end_);
  XVector = vector_.first;
  YVector = vector_.second;
  EXPECT_EQ(XVector.back(), 0);
  EXPECT_EQ(YVector.back(), 0);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}