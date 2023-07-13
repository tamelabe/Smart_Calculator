#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/main_model.h"

namespace s21 {
class Controller {
public:
    void setExpr(const std::string &expr) {
      model_.setExpr(expr);
    }
    void setXField(const std::string &x_field) {
      model_.setXValue(x_field);
    }
    void setXField(const double &x_field) {
      model_.setXValue(x_field);
    }
    void validateExpr() {
      model_.validateExpr();
    }
    void convertExpr() {
      model_.convertExpr();
    }
    void calculateExpr() {
      model_.calculateExpr();
    }
    std::string getResult() {
      return model_.getResult();
    }
    std::pair<int, std::string> getStatus() {
      return model_.getStatus();
    }
private:
    Model model_;
};
}

#endif  // SRC_CONTROLLER_CONTROLLER_H_
