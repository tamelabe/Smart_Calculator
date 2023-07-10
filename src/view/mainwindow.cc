#include "mainwindow.h"
#include "./ui_mainwindow.h"

//using namespace s21;

s21::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    ui_->label_result->setText("0");
    label_ = ui_->label_result;
    ;
    this->setFixedSize(760, 327);
    QShortcut *sc_backspace = new QShortcut(QKeySequence(Qt::Key_Backspace), this);
    QShortcut *sc_space = new QShortcut(QKeySequence(Qt::Key_Space), this);
    QShortcut *sc_e = new QShortcut(QKeySequence(Qt::Key_E), this);

    connect(ui_->butt_num_0, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_num_1, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_num_2, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_num_3, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_num_4, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_num_5, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_num_6, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_num_7, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_num_8, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_num_9, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_op_sum, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_op_sub, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_op_mul, SIGNAL(clicked()), this, SLOT(typeFunctions()));
    connect(ui_->butt_op_div, SIGNAL(clicked()), this, SLOT(typeFunctions()));
    connect(ui_->butt_bracket_op, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_bracket_cl, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_point, SIGNAL(clicked()), this, SLOT(typeChars()));

    connect(ui_->butt_fn_op_x, SIGNAL(clicked()), this, SLOT(typeChars()));
    connect(ui_->butt_fn_cos, SIGNAL(clicked()), this, SLOT(typeFunctions()));
    connect(ui_->butt_fn_sin, SIGNAL(clicked()), this, SLOT(typeFunctions()));
    connect(ui_->butt_fn_tan, SIGNAL(clicked()), this, SLOT(typeFunctions()));
    connect(ui_->butt_fn_acos, SIGNAL(clicked()), this, SLOT(typeFunctions()));
    connect(ui_->butt_fn_asin, SIGNAL(clicked()), this, SLOT(typeFunctions()));
    connect(ui_->butt_fn_atan, SIGNAL(clicked()), this, SLOT(typeFunctions()));
    connect(ui_->butt_sq_root, SIGNAL(clicked()), this, SLOT(typeFunctions()));
    connect(ui_->butt_ln, SIGNAL(clicked()), this, SLOT(typeFunctions()));
    connect(ui_->butt_log, SIGNAL(clicked()), this, SLOT(typeFunctions()));
    connect(ui_->butt_degree, SIGNAL(clicked()), this, SLOT(typeFunctions()));
    connect(ui_->butt_mod, SIGNAL(clicked()), this, SLOT(typeFunctions()));

    connect(ui_->butt_ac, SIGNAL(clicked()), this, SLOT(clearInput()));
    connect(ui_->butt_mode_graph, SIGNAL(clicked()), this, SLOT(initGraph()));
    connect(sc_backspace, SIGNAL(activated()), this, SLOT(deleteLastSym()));
    connect(sc_space, SIGNAL(activated()), this, SLOT(addSpace()));
    connect(sc_e, SIGNAL(activated()), this, SLOT(addESym()));


    connect(ui_->label_activate, SIGNAL(clicked()), this, SLOT(activateLabel()));
    connect(ui_->label_x_activate, SIGNAL(clicked()), this, SLOT(activateLabelX()));

    connect(ui_->butt_op_result, SIGNAL(clicked()), this, SLOT(calculate()));
}

s21::MainWindow::~MainWindow() {
    delete ui_;
}

void s21::MainWindow::activateLabelX() {
    ui_->label_result->setEnabled(false);
    ui_->label_x->setEnabled(true);
    label_ = ui_->label_x;
}

void s21::MainWindow::activateLabel() {
    ui_->label_x->setEnabled(false);
    ui_->label_result->setEnabled(true);
    label_ = ui_->label_result;
}

void s21::MainWindow::initGraph() {
    this->setFixedSize(760, 700);
}

void s21::MainWindow::typeChars() {
    if ((ui_->label_size->text()) == "255" && label_ == ui_->label_result)
        return;
    if ((label_->text().size()) >= 22 && label_ == ui_->label_x)
        return;
    QPushButton *button = (QPushButton *)sender();
    if (label_->text() == "0") {
        label_->setText(button->text());
    } else {
        QString new_result = label_->text() + button->text();
        label_->setText(new_result);
    }
    ui_->label_size->setText(QString::number(ui_->label_result->text().size()));
}


void s21::MainWindow::typeFunctions() {
    QPushButton *button = (QPushButton *)sender();
    QString new_result = button->toolTip();
    QTextDocument doc;
    doc.setHtml(new_result);
    new_result = doc.toPlainText();
    if ((ui_->label_size->text().toInt() + (new_result.size())) > 255)
        return;
    if (label_->text() != "0")
        new_result = label_->text() + new_result;
    label_->setText(new_result);
    ui_->label_size->setText(QString::number(ui_->label_result->text().size()));
}

void s21::MainWindow::addSpace() {
    if ((ui_->label_size->text()) == "255" && label_ == ui_->label_result)
        return;
    if ((label_->text().size()) >= 22 && label_ == ui_->label_x)
        return;
    if (label_->text() == "0")
        return;
    QString new_result = label_->text() + " ";
    label_->setText(new_result);
    ui_->label_size->setText(QString::number(ui_->label_result->text().size()));
}

void s21::MainWindow::addESym() {
    if ((ui_->label_size->text()) == "255" && label_ == ui_->label_result)
        return;
    if ((label_->text().size()) >= 22 && label_ == ui_->label_x)
        return;
    if (label_->text() == "0")
        return;
    QString new_result = label_->text() + "e";
    label_->setText(new_result);
    ui_->label_size->setText(QString::number(ui_->label_result->text().size()));
}

void s21::MainWindow::deleteLastSym() {
    if (label_->text() == "0" || label_->text() == "")
        return;
    QString new_result = label_->text();
    new_result = new_result.left(new_result.length() - 1);
    label_->setText(new_result);
    ui_->label_size->setText(QString::number(ui_->label_result->text().size()));
    if (ui_->label_result->text() == "")
        ui_->label_result->setText("0");
}

void s21::MainWindow::calculate() {
    if (ui_->label_result->text() == "0")
        return;
    if (ui_->label_result->text() == "Error") {
        ui_->label_result->setText("0");
        return;
    }
    ui_->label_x->setEnabled(false);
    ui_->label_result->setEnabled(true);
    std::string expr = ui_->label_result->text().toStdString();
    std::string expr_x = ui_->label_x->text().toStdString();
    expr = controller_.calculate(expr, expr_x);
    ui_->label_result->setText(QString::fromStdString(expr));

}

void s21::MainWindow::clearInput() {
    ui_->label_result->setText("0");
    ui_->label_x->setText("");
    ui_->label_size->setText("0");
}
