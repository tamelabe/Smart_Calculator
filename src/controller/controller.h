#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/main_model.h"

namespace s21 {
class Controller {
public:
    std::string calculate(const std::string &expr, const std::string &x_def) {
      model_.setExpr(expr, x_def);
      model_.prepareExpr();
      model_.validateExpr();
      model_.calculateExpr();
      return model_.getResultS();
    }
private:
    Model model_;
};
}

#endif  // SRC_CONTROLLER_CONTROLLER_H_
