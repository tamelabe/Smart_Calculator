#ifndef SRC_CONTROLLER_CREDIT_CONTROLLER_H_
#define SRC_CONTROLLER_CREDIT_CONTROLLER_H_

#include "../model/credit_model.h"

namespace s21 {
class CreditController {
 public:
  void setParams(const CreditParams &params) { model_.setParams(params); }
  void calculate() { model_.calculate(); }
  CreditParams getResult() { return model_.getResult(); }
  std::pair<int, std::string> getStatus() { return model_.getStatus(); }

 private:
  CreditModel model_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CREDIT_CONTROLLER_H_