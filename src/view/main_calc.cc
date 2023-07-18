#include "main_calc.h"
#include "./ui_main_calc.h"


s21::MainCalc::MainCalc(QWidget *parent)
    : QWidget(parent)
    , ui_(new Ui::MainCalc)
{
    initElements();
    connectSlots();
}

s21::MainCalc::~MainCalc() {
    delete ui_;
}

void s21::MainCalc::connectSlots() {
    QShortcut *sc_backspace = new QShortcut(QKeySequence(Qt::Key_Backspace), this);
    QShortcut *sc_space = new QShortcut(QKeySequence(Qt::Key_Space), this);
    QShortcut *sc_e = new QShortcut(QKeySequence(Qt::Key_E), this);

    connect(ui_->butt_mode_credit, SIGNAL(clicked()), this, SLOT(openCredit()));

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
    connect(ui_->butt_op_result, SIGNAL(clicked()), this, SLOT(calculate()));

    connect(ui_->butt_ac, SIGNAL(clicked()), this, SLOT(clearInput()));
    connect(ui_->butt_mode_graph, SIGNAL(clicked()), this, SLOT(createGraph()));
    connect(ui_->butt_graph_hide, SIGNAL(clicked()), this, SLOT(hideGraph()));

    connect(sc_backspace, SIGNAL(activated()), this, SLOT(deleteLastSym()));
    connect(sc_space, SIGNAL(activated()), this, SLOT(addSymbol()));
    connect(sc_e, SIGNAL(activated()), this, SLOT(addSymbol()));

    connect(ui_->label_activate, SIGNAL(clicked()), this, SLOT(activateLabel()));
    connect(ui_->label_x_activate, SIGNAL(clicked()), this, SLOT(activateLabelX()));
}

void s21::MainCalc::openCredit() {
    if (credit_.isVisible()) {
        credit_.hide();
    } else {
        credit_.show();
    }
}

void s21::MainCalc::addSymbol() {
    if ((ui_->label_size->text()) == "255" && label_ == ui_->label_result)
        return;
    if ((label_->text().size()) >= 22 && label_ == ui_->label_x)
        return;
    if (label_->text() == "0")
        return;
    QShortcut *button = qobject_cast<QShortcut*>(sender());
    QString button_text = button->key().toString().toLower();
    if (button_text == "space") button_text = " ";
    QString new_result = label_->text() + button_text;
    label_->setText(new_result);
    ui_->label_size->setText(QString::number(ui_->label_result->text().size()));
}

void s21::MainCalc::initElements() {
    ui_->setupUi(this);
    ui_->label_result->setText("0");
    label_ = ui_->label_result;
    this->setFixedSize(760, 327);
    scaleSpins(false);
}

void s21::MainCalc::activateSpins() {
    ui_->label_result->setEnabled(false);
    ui_->label_x->setEnabled(false);
    scaleSpins(true);
}

void s21::MainCalc::scaleSpins(bool state) {
    ui_->spinBox_XS->setEnabled(state);
    ui_->spinBox_XF->setEnabled(state);
    ui_->spinBox_YS->setEnabled(state);
    ui_->spinBox_YF->setEnabled(state);
}

void s21::MainCalc::activateLabelX() {
    ui_->label_result->setEnabled(false);
    ui_->label_x->setEnabled(true);
    scaleSpins(false);
    label_ = ui_->label_x;
}

void s21::MainCalc::activateLabel() {
    ui_->label_x->setEnabled(false);
    ui_->label_result->setEnabled(true);
    scaleSpins(false);
    label_ = ui_->label_result;
}

void s21::MainCalc::initGraph() {
    this->setFixedSize(760, 700);
    ui_->label_result->setEnabled(false);
    ui_->label_x->setEnabled(false);
    scaleSpins(true);
    ui_->graph_window->xAxis->setRange(30, 30);
    ui_->graph_window->yAxis->setRange(30, 30);
    ui_->graph_window->addGraph();
}

void s21::MainCalc::createGraph() {
    std::string expr = ui_->label_result->text().toStdString();
    initGraph();
    if (!checkGraphFunc(expr)) return;
    ui_->graph_window->clearGraphs();
    double x_begin = ui_->spinBox_XS->value();
    double y_begin = ui_->spinBox_YS->value();
    double x_end = ui_->spinBox_XF->value();
    double y_end = ui_->spinBox_YF->value();
    std::pair<std::vector<double>, std::vector<double>> vector = controller_.getGraphVector(x_begin, x_end, y_begin, y_end);
    ui_->graph_window->xAxis->setRange(x_begin, x_end);
    ui_->graph_window->yAxis->setRange(y_begin, y_end);
    ui_->graph_window->addGraph();
    QVector<double> vec_x(vector.first.begin(), vector.first.end());
    QVector<double> vec_y(vector.second.begin(), vector.second.end());
    ui_->graph_window->graph(0)->addData(vec_x, vec_y);
    ui_->graph_window->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui_->graph_window->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
    ui_->graph_window->replot();
}

bool s21::MainCalc::checkGraphFunc(const std::string &expr) {
    controller_.setExpr(expr);
    controller_.validateExpr();
    controller_.convertExpr();
    if (controller_.getStatus().first % 10 != 0) {
        return true;
    } else {
        ui_->label_result->setText(QString::fromStdString("Error"));
        return false;
    }
}

void s21::MainCalc::hideGraph() {
    this->setFixedSize(760, 327);
}

void s21::MainCalc::typeChars() {
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


void s21::MainCalc::typeFunctions() {
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

void s21::MainCalc::deleteLastSym() {
    if (label_->text() == "0" || label_->text() == "")
        return;
    QString new_result = label_->text();
    new_result = new_result.left(new_result.length() - 1);
    label_->setText(new_result);
    ui_->label_size->setText(QString::number(ui_->label_result->text().size()));
    if (ui_->label_result->text() == "")
        ui_->label_result->setText("0");
}

void s21::MainCalc::calculate() {
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
    controller_.setExpr(expr);
    controller_.setXField(expr_x);
    controller_.validateExpr();
    controller_.convertExpr();
    controller_.calculateExpr();
    expr = controller_.getResult();
    ui_->label_result->setText(QString::fromStdString(expr));

}

void s21::MainCalc::clearInput() {
    ui_->label_result->setText("0");
    ui_->label_x->setText("");
    ui_->label_size->setText("0");
}
