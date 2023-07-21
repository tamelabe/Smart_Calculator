#ifndef MAIN_CALC_H
#define MAIN_CALC_H

#include <QShortcut>
#include <QWidget>
#include <string>

#include "../controller/main_controller.h"
#include "./credit_calc.h"
#include "QtWidgets/qlabel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainCalc;
}
QT_END_NAMESPACE

namespace s21 {

class MainCalc : public QWidget {
  Q_OBJECT

 public:
  MainCalc(QWidget *parent = nullptr);
  ~MainCalc();

 private:
  Ui::MainCalc *ui_;
  QLabel *label_;
  MainController controller_;
  CreditCalc credit_;
  void scaleSpins(bool state);
  void initGraph();
  bool checkGraphFunc(const std::string &expr);
  void connectSlots();

 private slots:
  void initElements();
  void activateLabelX();
  void activateLabel();
  void activateSpins();
  void typeChars();
  void typeFunctions();
  void deleteLastSym();
  void clearInput();
  void createGraph();
  void hideGraph();
  void calculate();
  void addSymbol();
  void openCredit();
};
}  // namespace s21
#endif  // MAIN_CALC_H
