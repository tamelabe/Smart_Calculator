#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
class Controller {
public:
    void calculate(std::string &expr, const std::string &x_def) {
        model_.calculate(expr, x_def);
    }
private:
    Model model_;
};
}

#endif  // SRC_CONTROLLER_CONTROLLER_H_
