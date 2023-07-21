#ifndef SRC_CREDIT_CALC_H
#define SRC_CREDIT_CALC_H

#include <QWidget>
#include <QMessageBox>

#include "../resources/contain_objects.h"
#include "../controller/credit_controller.h"

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
    int table_rows_{};
    CreditParams credit_data_;
    CreditController controller_;
    void parseInputValues();
    void setCalculatedValues();
    void initWindow();
    void initTable();
    void fillCeils();
    void deallocateCeils();
    bool errCheck();

private slots:
    void calculate();
    void hideGraph();
};
}  // namespace s21
#endif // SRC_CREDIT_CALC_H
