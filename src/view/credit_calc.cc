#include "credit_calc.h"

#include "ui_credit_calc.h"

s21::CreditCalc::CreditCalc(QWidget *parent)
    : QWidget(parent), ui_(new Ui::CreditCalc) {
  initWindow();
}

s21::CreditCalc::~CreditCalc() {
  deallocateCeils();
  delete ui_;
}

void s21::CreditCalc::initWindow() {
  ui_->setupUi(this);
  this->setFixedSize(280, 500);
  connect(ui_->bt_calculate, SIGNAL(clicked()), this, SLOT(calculate()));
  connect(ui_->bt_hide, SIGNAL(clicked()), this, SLOT(hideGraph()));
}

void s21::CreditCalc::calculate() {
  parseInputValues();
  controller_.setParams(credit_data_);
  if (errCheck()) return;
  controller_.calculate();
  setCalculatedValues();
  if (ui_->box_type->currentText() == "Differentiated" &&
      ui_->box_period->value() > 1) {
    deallocateCeils();
    initTable();
    fillCeils();
    this->setFixedSize(550, 500);
  } else {
    this->setFixedSize(280, 500);
  }
}

void s21::CreditCalc::parseInputValues() {
  credit_data_.type = ui_->box_type->currentText().toStdString();
  credit_data_.loan = ui_->box_loan->value();
  credit_data_.period = ui_->box_period->value();
  credit_data_.rate = ui_->box_rate->value();
}

void s21::CreditCalc::setCalculatedValues() {
  QString month_pay =
      QString::fromStdString(controller_.getResult().month_pay.front());
  QString overpay = QString::fromStdString(controller_.getResult().overpay);
  QString total_pay = QString::fromStdString(controller_.getResult().total_pay);
  ui_->label_month_pay->setText(month_pay);
  ui_->label_overpay->setText(overpay);
  ui_->label_total_pay->setText(total_pay);
  if (ui_->box_type->currentText() == "Differentiated" &&
      ui_->box_period->value() > 1) {
    QString month_pay_back =
        QString::fromStdString(controller_.getResult().month_pay.back());
    QString month_pay_delta = month_pay + "..." + month_pay_back;
    ui_->label_month_pay->setText(month_pay_delta);
  }
}

bool ::s21::CreditCalc::errCheck() {
  if (controller_.getStatus().first % 10 == 0) {
    QString message = QString::fromStdString(controller_.getStatus().second);
    QMessageBox::warning(this, "Warning", message);
    return true;
  } else {
    return false;
  }
}

void s21::CreditCalc::initTable() {
  ui_->tableWidget->clearContents();
  table_rows_ = ui_->box_period->value();
  ui_->tableWidget->setRowCount(table_rows_);
  QStringList header;
  header << "Month"
         << "Payment";
  ui_->tableWidget->setHorizontalHeaderLabels(header);
  ui_->tableWidget->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
}

void s21::CreditCalc::fillCeils() {
  std::vector month_pay_v_(controller_.getResult().month_pay);
  for (int i = 0; i < ui_->box_period->value(); ++i) {
    QTableWidgetItem *val =
        new QTableWidgetItem(QString::fromStdString(month_pay_v_[i]));
    QTableWidgetItem *num = new QTableWidgetItem(QString::number(i + 1));
    val->setFlags(val->flags() & ~Qt::ItemIsEditable);
    num->setFlags(num->flags() & ~Qt::ItemIsEditable);
    num->setTextAlignment(Qt::AlignCenter);
    ui_->tableWidget->setItem(i, 0, num);
    ui_->tableWidget->setItem(i, 1, val);
  }
}

void s21::CreditCalc::hideGraph() { this->setFixedSize(280, 500); }

void s21::CreditCalc::deallocateCeils() {
  if (ui_->tableWidget->item(0, 0) == nullptr) {
    return;
  }
  for (int i = 0; i < table_rows_; ++i) {
    QTableWidgetItem *num = ui_->tableWidget->item(i, 0);
    QTableWidgetItem *val = ui_->tableWidget->item(i, 1);
    delete num;
    delete val;
  }
}
