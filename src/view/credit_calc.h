#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include <QWidget>

namespace Ui {
class CreditCalc;
}

namespace s21 {

class CreditCalc : public QWidget
{
    Q_OBJECT

public:
    explicit CreditCalc(QWidget *parent = nullptr);
    ~CreditCalc();

private:
    Ui::CreditCalc *ui_;

private slots:

};
}  // namespace s21
#endif // CREDIT_CALC_H
