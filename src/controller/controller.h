#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../view/mainwindow.h"

namespace s21 {
    class Controller {
    public:
        void calculate(std::string &expr, const std::string &x_def) {
            expr = "Hello!";
        }
    };
}

#endif  // SRC_CONTROLLER_CONTROLLER_H_