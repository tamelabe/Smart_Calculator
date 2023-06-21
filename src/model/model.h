#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include "../resources/exprtk.hpp"

namespace s21 {
    class Model {
    public:
        void calculate(std::string &expr, const std::string &x_def) {

        }
    private:
        std::string res_;
        void validate(std::string &expr);
    };
}

#endif  // SRC_MODEL_MODEL_H_