#ifndef SRC_RESOURCES_CONTAIN_OBJECTS_H_
#define SRC_RESOURCES_CONTAIN_OBJECTS_H_

#include <string>
#include <vector>

namespace s21 {
struct CreditParams {
  CreditParams() = default;
  ~CreditParams() = default;

 public:
  CreditParams(const std::string &type_i, double loan_i, int period_i,
               double rate_i)
      : type(type_i), loan(loan_i), period(period_i), rate(rate_i) {}
  void setInput(const std::string &type_i, double loan_i, int period_i,
                double rate_i) {
    type = type_i;
    loan = loan_i;
    period = period_i;
    rate = rate_i;
  }
  std::string type{};
  double loan{};
  int period{};
  double rate{};
  std::vector<std::string> month_pay;
  std::string overpay{};
  std::string total_pay{};
};
}  // namespace s21

#endif  // SRC_RESOURCES_CONTAIN_OBJECTS_H_
