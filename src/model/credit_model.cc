#include "credit_model.h"

/**
 * @brief Sets calculation parameters
 * @param params CreditParams struct object
 */
void s21::CreditModel::setParams(CreditParams params) {
  if (!params.loan || !params.rate || !params.period) {
    status_ = {10, "Set: Fail (values must be bigger than zero)"};
    return;
  }
  params_.type = params.type;
  params_.loan = params.loan;
  params_.period = params.period;
  params_.rate = params.rate;
  status_ = {11, "Set: Success"};
}

/**
 * @brief Calculates set params
 */
void s21::CreditModel::calculate() {
  if (status_.first % 10 == 0) return;
  month_pay_.clear();
  if (params_.type == "Annuity") {
    calculateAnnuity();
  } else {
    calculateDifferentiated();
  }
  convertOutput();
  status_ = {21, "Calculate: Success"};
}

/**
 * @brief Annuity method calculation
 */
void s21::CreditModel::calculateAnnuity() {
  double month_rate = params_.rate / 12 * 0.01;
  double month_pay = (params_.loan * month_rate) /
                     (1 - std::pow((1 + month_rate), (params_.period * -1)));
  month_pay = std::round(month_pay * 100) / 100;
  month_pay_.push_back(month_pay);
  total_pay_ = month_pay_.front() * params_.period;
  overpay_ = total_pay_ - params_.loan;
}

/**
 * Differentiated method calculation
 */
void s21::CreditModel::calculateDifferentiated() {
  double month_rate = params_.rate / 12 * 0.01;
  double month_pay{};
  total_pay_ = 0;
  double avg_pay = params_.loan / params_.period;
  for (int i = 0; i < params_.period; ++i) {
    month_pay = avg_pay + (params_.loan - i * avg_pay) * month_rate;
    total_pay_ += month_pay;
    month_pay_.push_back(month_pay);
  }
  overpay_ = total_pay_ - params_.loan;
}

/**
 * Convert all output params to std::string
 */
void s21::CreditModel::convertOutput() {
  params_.month_pay.clear();
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
std::string s21::CreditModel::toStdString(const double &value) {
  std::ostringstream stream;
  std::string result;
  stream.precision(2);
  stream << std::fixed << value;
  result = stream.str();
  return result;
}