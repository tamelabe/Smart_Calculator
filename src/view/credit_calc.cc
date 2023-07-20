#include "credit_calc.h"
#include "ui_credit_calc.h"

s21::CreditCalc::CreditCalc(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::CreditCalc)
{
    ui_->setupUi(this);
    this->setFixedSize(300, 500);
    connect(ui_->bt_calculate, SIGNAL(clicked()), this, SLOT(calculate()));
}

s21::CreditCalc::~CreditCalc()
{
    delete ui_;
}

void s21::CreditCalc::calculate() {
    credit_data_.type = ui_->box_type->currentText().toStdString();
    credit_data_.loan = ui_->box_loan->value();
    credit_data_.period = ui_->box_period->value();
    credit_data_.rate = ui_->box_rate->value();
    controller_.setParams(credit_data_);
    controller_.calculate();
    QString month_pay = QString::fromStdString(controller_.getResult().month_pay.front());
    QString overpay = QString::fromStdString(controller_.getResult().overpay);
    QString total_pay = QString::fromStdString(controller_.getResult().total_pay);
    ui_->label_month_pay->setText(month_pay);
    ui_->label_overpay->setText(overpay);
    ui_->label_total_pay->setText(total_pay);
    if (ui_->box_type->currentText() == "Differentiated" && ui_->box_period->value() != 1) {
        QString month_pay_b = month_pay + "..." + QString::fromStdString(controller_.getResult().month_pay.back());
        ui_->label_month_pay->setText(month_pay_b);

        ui_->tableWidget->clearContents();
        ui_->tableWidget->setRowCount(ui_->box_period->value() + 1);
        QStringList header;
        header << "Month num" << "payment amount";
        ui_->tableWidget->setHorizontalHeaderLabels(header);
        std::vector month_pay_v_(controller_.getResult().month_pay);
        for (int i = 1; i <= ui_->box_period->value(); ++i) {
            QTableWidgetItem *val  = new QTableWidgetItem(QString::fromStdString(month_pay_v_[i - 1]));
            QTableWidgetItem *num = new QTableWidgetItem(QString::number(i));
            val->setFlags(val->flags() & ~Qt::ItemIsEditable);
            num->setFlags(num->flags() & ~Qt::ItemIsEditable);
            ui_->tableWidget->setItem(i, 0, num);
            ui_->tableWidget->setItem(i, 1, val);
        }
        this->setFixedSize(500, 500);
    }
}
