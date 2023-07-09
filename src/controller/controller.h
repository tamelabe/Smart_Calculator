#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/main_model.h"

namespace s21 {
class Controller {
public:
    void calculate(std::string &expr, const std::string &x_def) {
      model_.setExpr(expr, x_def);
      model_.prepareExpr();
      model_.validateExpr();
      model_.calculateExpr();
      model_.replaceStr();
    }
private:
    Model model_;
};
}

#endif  // SRC_CONTROLLER_CONTROLLER_H_
