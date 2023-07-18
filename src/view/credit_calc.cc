#include "credit_calc.h"
#include "ui_credit_calc.h"

s21::CreditCalc::CreditCalc(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::CreditCalc)
{
    ui_->setupUi(this);
}

s21::CreditCalc::~CreditCalc()
{
    delete ui_;
}

