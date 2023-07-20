#ifndef SRC_MODEL_CREDIT_MODEL_H_
#define SRC_MODEL_CREDIT_MODEL_H_

#include "../resources/contain_objects.h"
#include <cmath>
#include <sstream>

namespace s21 {
class CreditModel {
 public:
  CreditModel() = default;
  ~CreditModel() = default;
  /**
   * @brief Sets calculation parameters
   * @param params CreditParams struct object
   */
  void setParams(CreditParams params) {
    params_.type = params.type;
    params_.loan = params.loan;
    params_.period = params.period;
    params_.rate = params.rate;
  }
  /**
   * @brief Calculates set params
   */
  void calculate() {
    if (params_.type == "Annuity") {
      calculateAnnuity();
    } else {
      calculateDifferentiated();
    }
    convertOutput();
  }
  /**
   * @return Returns calculated CreditParams struct object
   */
  CreditParams getResult() {
    return params_;
  }

 private:
  CreditParams params_;
  std::vector<double> month_pay_{};
  double overpay_{};
  double total_pay_{};

  /**
   * @brief Annuity method calculation
   */
  void calculateAnnuity() {
    double month_rate = params_.rate / 12 * 0.01;
    double month_pay = (params_.loan * month_rate) / (1 - std::pow((1 + month_rate), (params_.period * -1)));
    month_pay = std::round(month_pay * 100) / 100;
    month_pay_.push_back(month_pay);
    total_pay_ = month_pay_.front() * params_.period;
    overpay_ = total_pay_ - params_.loan;
  }
  /**
   * Differentiated method calculation
   */
  void calculateDifferentiated() {
    double month_rate = params_.rate / 12 * 0.01;
    double month_pay{};
    total_pay_ = 0;
    double avg_pay = params_.loan / params_.period;
    for(int i = 0; i < params_.period; ++i) {
      month_pay = avg_pay + (params_.loan - i * avg_pay) * month_rate;
      total_pay_ += month_pay;
      month_pay_.push_back(month_pay);
    }
    overpay_ = total_pay_ - params_.loan;
  }
  /**
   * Convert all output params to std::string
   */
  void convertOutput() {
    params_.overpay = toStdString(overpay_);
    params_.total_pay = toStdString(total_pay_);
    for (size_t i = 0; i < month_pay_.size(); ++i)
      params_.month_pay.push_back(toStdString(month_pay_[i]));
  }
  /**
   * Converts double to std::string
   * @param value (double)
   * @return std::string with an accuracy of 2 decimal places
   */
  std::string toStdString(const double &value) {
    std::ostringstream stream;
    std::string result;
    stream.precision(2);
    stream << std::fixed << value;
    result = stream.str();
    return result;
  }
};
}  // namespace s21

#endif  // SRC_MODEL_CREDIT_MODEL_H_
