#ifndef SRC_MODEL_CREDIT_MODEL_H_
#define SRC_MODEL_CREDIT_MODEL_H_

#include <cmath>
#include <sstream>
#include <utility>

#include "../resources/contain_objects.h"

namespace s21 {
class CreditModel {
 public:
  CreditModel() { status_ = {0, "Init: Success"}; }
  ~CreditModel() = default;

  void setParams(CreditParams params);
  void calculate();
  /**
   * @return Returns calculated CreditParams struct object
   */
  CreditParams getResult() { return params_; }
  /**
   * @return Model status
   */
  std::pair<int, std::string> getStatus() { return status_; }

 private:
  CreditParams params_;
  std::vector<double> month_pay_{};
  double overpay_{};
  double total_pay_{};
  std::pair<int, std::string> status_;

  void calculateAnnuity();
  void calculateDifferentiated();
  void convertOutput();
  std::string toStdString(const double &value);
};
}  // namespace s21

#endif  // SRC_MODEL_CREDIT_MODEL_H_
