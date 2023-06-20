/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_size_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *butt_fn_asin;
    QPushButton *butt_bracket_op;
    QPushButton *butt_fn_tan;
    QPushButton *butt_mode_deposit;
    QPushButton *butt_num_4;
    QPushButton *butt_percent;
    QPushButton *butt_fn_atan;
    QPushButton *butt_num_0;
    QPushButton *butt_num_2;
    QPushButton *butt_op_result;
    QPushButton *butt_fn_op_x;
    QPushButton *butt_bracket_cl;
    QPushButton *butt_num_6;
    QPushButton *butt_num_1;
    QPushButton *butt_degree;
    QPushButton *butt_fn_cos;
    QPushButton *butt_op_mul;
    QPushButton *butt_mod;
    QPushButton *butt_sq_root;
    QPushButton *butt_op_sub;
    QPushButton *butt_fn_sin;
    QPushButton *butt_op_sum;
    QPushButton *butt_point;
    QPushButton *butt_num_9;
    QPushButton *butt_num_7;
    QPushButton *butt_num_3;
    QPushButton *butt_log;
    QPushButton *butt_mode_graph;
    QPushButton *butt_fn_acos;
    QPushButton *butt_ln;
    QPushButton *butt_ac;
    QPushButton *butt_num_8;
    QPushButton *butt_num_5;
    QPushButton *butt_mode_credit;
    QPushButton *butt_op_div;
    QLabel *label_result;
    QLabel *label_size;
    QLabel *label;
    QLabel *label_additional;
    QPushButton *label_activate;
    QLabel *label_x;
    QPushButton *label_x_activate;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(772, 700);
        MainWindow->setMinimumSize(QSize(760, 327));
        MainWindow->setMaximumSize(QSize(772, 700));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(772, 500));
        centralwidget->setAutoFillBackground(false);
        label_size_2 = new QLabel(centralwidget);
        label_size_2->setObjectName(QString::fromUtf8("label_size_2"));
        label_size_2->setGeometry(QRect(700, 35, 28, 16));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(40);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_size_2->sizePolicy().hasHeightForWidth());
        label_size_2->setSizePolicy(sizePolicy);
        label_size_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(24, 120, 711, 191));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        butt_fn_asin = new QPushButton(layoutWidget);
        butt_fn_asin->setObjectName(QString::fromUtf8("butt_fn_asin"));

        gridLayout->addWidget(butt_fn_asin, 1, 1, 1, 1);

        butt_bracket_op = new QPushButton(layoutWidget);
        butt_bracket_op->setObjectName(QString::fromUtf8("butt_bracket_op"));

        gridLayout->addWidget(butt_bracket_op, 0, 3, 1, 1);

        butt_fn_tan = new QPushButton(layoutWidget);
        butt_fn_tan->setObjectName(QString::fromUtf8("butt_fn_tan"));

        gridLayout->addWidget(butt_fn_tan, 3, 0, 1, 1);

        butt_mode_deposit = new QPushButton(layoutWidget);
        butt_mode_deposit->setObjectName(QString::fromUtf8("butt_mode_deposit"));

        gridLayout->addWidget(butt_mode_deposit, 0, 1, 1, 1);

        butt_num_4 = new QPushButton(layoutWidget);
        butt_num_4->setObjectName(QString::fromUtf8("butt_num_4"));
        butt_num_4->setEnabled(true);
        butt_num_4->setSizeIncrement(QSize(0, 0));
        butt_num_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"   border: 1px solid gray;\n"
"	border-radius: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(192, 192, 192), stop: 1 rgb(169, 169, 169));\n"
"}"));

        gridLayout->addWidget(butt_num_4, 2, 3, 1, 1);

        butt_percent = new QPushButton(layoutWidget);
        butt_percent->setObjectName(QString::fromUtf8("butt_percent"));

        gridLayout->addWidget(butt_percent, 0, 5, 1, 1);

        butt_fn_atan = new QPushButton(layoutWidget);
        butt_fn_atan->setObjectName(QString::fromUtf8("butt_fn_atan"));

        gridLayout->addWidget(butt_fn_atan, 3, 1, 1, 1);

        butt_num_0 = new QPushButton(layoutWidget);
        butt_num_0->setObjectName(QString::fromUtf8("butt_num_0"));
        butt_num_0->setEnabled(true);
        butt_num_0->setSizeIncrement(QSize(0, 0));
        butt_num_0->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"   border: 1px solid gray;\n"
"	border-radius: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(192, 192, 192), stop: 1 rgb(169, 169, 169));\n"
"}"));

        gridLayout->addWidget(butt_num_0, 4, 3, 1, 1);

        butt_num_2 = new QPushButton(layoutWidget);
        butt_num_2->setObjectName(QString::fromUtf8("butt_num_2"));
        butt_num_2->setEnabled(true);
        butt_num_2->setSizeIncrement(QSize(0, 0));
        butt_num_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"   border: 1px solid gray;\n"
"	border-radius: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(192, 192, 192), stop: 1 rgb(169, 169, 169));\n"
"}"));

        gridLayout->addWidget(butt_num_2, 3, 4, 1, 1);

        butt_op_result = new QPushButton(layoutWidget);
        butt_op_result->setObjectName(QString::fromUtf8("butt_op_result"));

        gridLayout->addWidget(butt_op_result, 4, 5, 1, 1);

        butt_fn_op_x = new QPushButton(layoutWidget);
        butt_fn_op_x->setObjectName(QString::fromUtf8("butt_fn_op_x"));
        butt_fn_op_x->setLayoutDirection(Qt::LeftToRight);
        butt_fn_op_x->setFlat(false);

        gridLayout->addWidget(butt_fn_op_x, 4, 1, 1, 1);

        butt_bracket_cl = new QPushButton(layoutWidget);
        butt_bracket_cl->setObjectName(QString::fromUtf8("butt_bracket_cl"));

        gridLayout->addWidget(butt_bracket_cl, 0, 4, 1, 1);

        butt_num_6 = new QPushButton(layoutWidget);
        butt_num_6->setObjectName(QString::fromUtf8("butt_num_6"));
        butt_num_6->setEnabled(true);
        butt_num_6->setSizeIncrement(QSize(0, 0));
        butt_num_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"   border: 1px solid gray;\n"
"	border-radius: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(192, 192, 192), stop: 1 rgb(169, 169, 169));\n"
"}"));

        gridLayout->addWidget(butt_num_6, 2, 5, 1, 1);

        butt_num_1 = new QPushButton(layoutWidget);
        butt_num_1->setObjectName(QString::fromUtf8("butt_num_1"));
        butt_num_1->setEnabled(true);
        butt_num_1->setSizeIncrement(QSize(0, 0));
        butt_num_1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"   border: 1px solid gray;\n"
"	border-radius: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(192, 192, 192), stop: 1 rgb(169, 169, 169));\n"
"}"));

        gridLayout->addWidget(butt_num_1, 3, 3, 1, 1);

        butt_degree = new QPushButton(layoutWidget);
        butt_degree->setObjectName(QString::fromUtf8("butt_degree"));

        gridLayout->addWidget(butt_degree, 4, 2, 1, 1);

        butt_fn_cos = new QPushButton(layoutWidget);
        butt_fn_cos->setObjectName(QString::fromUtf8("butt_fn_cos"));

        gridLayout->addWidget(butt_fn_cos, 2, 0, 1, 1);

        butt_op_mul = new QPushButton(layoutWidget);
        butt_op_mul->setObjectName(QString::fromUtf8("butt_op_mul"));

        gridLayout->addWidget(butt_op_mul, 2, 6, 1, 1);

        butt_mod = new QPushButton(layoutWidget);
        butt_mod->setObjectName(QString::fromUtf8("butt_mod"));

        gridLayout->addWidget(butt_mod, 0, 2, 1, 1);

        butt_sq_root = new QPushButton(layoutWidget);
        butt_sq_root->setObjectName(QString::fromUtf8("butt_sq_root"));

        gridLayout->addWidget(butt_sq_root, 3, 2, 1, 1);

        butt_op_sub = new QPushButton(layoutWidget);
        butt_op_sub->setObjectName(QString::fromUtf8("butt_op_sub"));

        gridLayout->addWidget(butt_op_sub, 3, 6, 1, 1);

        butt_fn_sin = new QPushButton(layoutWidget);
        butt_fn_sin->setObjectName(QString::fromUtf8("butt_fn_sin"));

        gridLayout->addWidget(butt_fn_sin, 1, 0, 1, 1);

        butt_op_sum = new QPushButton(layoutWidget);
        butt_op_sum->setObjectName(QString::fromUtf8("butt_op_sum"));

        gridLayout->addWidget(butt_op_sum, 4, 6, 1, 1);

        butt_point = new QPushButton(layoutWidget);
        butt_point->setObjectName(QString::fromUtf8("butt_point"));

        gridLayout->addWidget(butt_point, 4, 4, 1, 1);

        butt_num_9 = new QPushButton(layoutWidget);
        butt_num_9->setObjectName(QString::fromUtf8("butt_num_9"));
        butt_num_9->setEnabled(true);
        butt_num_9->setSizeIncrement(QSize(0, 0));
        butt_num_9->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"   border: 1px solid gray;\n"
"	border-radius: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(192, 192, 192), stop: 1 rgb(169, 169, 169));\n"
"}"));

        gridLayout->addWidget(butt_num_9, 1, 5, 1, 1);

        butt_num_7 = new QPushButton(layoutWidget);
        butt_num_7->setObjectName(QString::fromUtf8("butt_num_7"));
        butt_num_7->setEnabled(true);
        butt_num_7->setSizeIncrement(QSize(0, 0));
        butt_num_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"   border: 1px solid gray;\n"
"	border-radius: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(192, 192, 192), stop: 1 rgb(169, 169, 169));\n"
"}"));

        gridLayout->addWidget(butt_num_7, 1, 3, 1, 1);

        butt_num_3 = new QPushButton(layoutWidget);
        butt_num_3->setObjectName(QString::fromUtf8("butt_num_3"));
        butt_num_3->setEnabled(true);
        butt_num_3->setSizeIncrement(QSize(0, 0));
        butt_num_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"   border: 1px solid gray;\n"
"	border-radius: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(192, 192, 192), stop: 1 rgb(169, 169, 169));\n"
"}"));

        gridLayout->addWidget(butt_num_3, 3, 5, 1, 1);

        butt_log = new QPushButton(layoutWidget);
        butt_log->setObjectName(QString::fromUtf8("butt_log"));

        gridLayout->addWidget(butt_log, 2, 2, 1, 1);

        butt_mode_graph = new QPushButton(layoutWidget);
        butt_mode_graph->setObjectName(QString::fromUtf8("butt_mode_graph"));

        gridLayout->addWidget(butt_mode_graph, 4, 0, 1, 1);

        butt_fn_acos = new QPushButton(layoutWidget);
        butt_fn_acos->setObjectName(QString::fromUtf8("butt_fn_acos"));

        gridLayout->addWidget(butt_fn_acos, 2, 1, 1, 1);

        butt_ln = new QPushButton(layoutWidget);
        butt_ln->setObjectName(QString::fromUtf8("butt_ln"));

        gridLayout->addWidget(butt_ln, 1, 2, 1, 1);

        butt_ac = new QPushButton(layoutWidget);
        butt_ac->setObjectName(QString::fromUtf8("butt_ac"));

        gridLayout->addWidget(butt_ac, 0, 6, 1, 1);

        butt_num_8 = new QPushButton(layoutWidget);
        butt_num_8->setObjectName(QString::fromUtf8("butt_num_8"));
        butt_num_8->setEnabled(true);
        butt_num_8->setSizeIncrement(QSize(0, 0));
        butt_num_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"   border: 1px solid gray;\n"
"	border-radius: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(192, 192, 192), stop: 1 rgb(169, 169, 169));\n"
"}"));

        gridLayout->addWidget(butt_num_8, 1, 4, 1, 1);

        butt_num_5 = new QPushButton(layoutWidget);
        butt_num_5->setObjectName(QString::fromUtf8("butt_num_5"));
        butt_num_5->setEnabled(true);
        butt_num_5->setSizeIncrement(QSize(0, 0));
        butt_num_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"   border: 1px solid gray;\n"
"	border-radius: 6px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 rgb(192, 192, 192), stop: 1 rgb(169, 169, 169));\n"
"}"));

        gridLayout->addWidget(butt_num_5, 2, 4, 1, 1);

        butt_mode_credit = new QPushButton(layoutWidget);
        butt_mode_credit->setObjectName(QString::fromUtf8("butt_mode_credit"));
        butt_mode_credit->setEnabled(true);
        QPalette palette;
        QBrush brush(QColor(147, 150, 153, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(64, 65, 66, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        butt_mode_credit->setPalette(palette);
        butt_mode_credit->setFocusPolicy(Qt::TabFocus);

        gridLayout->addWidget(butt_mode_credit, 0, 0, 1, 1);

        butt_op_div = new QPushButton(layoutWidget);
        butt_op_div->setObjectName(QString::fromUtf8("butt_op_div"));

        gridLayout->addWidget(butt_op_div, 1, 6, 1, 1);

        label_result = new QLabel(centralwidget);
        label_result->setObjectName(QString::fromUtf8("label_result"));
        label_result->setGeometry(QRect(23, 30, 711, 71));
        QFont font;
        font.setPointSize(18);
        label_result->setFont(font);
        label_result->setTabletTracking(false);
        label_result->setLayoutDirection(Qt::LeftToRight);
        label_result->setStyleSheet(QString::fromUtf8("QLabel {\n"
"  qproperty-alignment: 'AlignVCenter | AlignRight';\n"
"  border: 1px solid gray;\n"
"}\n"
"background-color : white;"));
        label_result->setScaledContents(false);
        label_result->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_result->setMargin(8);
        label_size = new QLabel(centralwidget);
        label_size->setObjectName(QString::fromUtf8("label_size"));
        label_size->setGeometry(QRect(682, 35, 16, 16));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_size->sizePolicy().hasHeightForWidth());
        label_size->setSizePolicy(sizePolicy1);
        label_size->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(550, 10, 21, 16));
        label_additional = new QLabel(centralwidget);
        label_additional->setObjectName(QString::fromUtf8("label_additional"));
        label_additional->setGeometry(QRect(543, 10, 191, 21));
        label_additional->setFont(font);
        label_additional->setTabletTracking(false);
        label_additional->setLayoutDirection(Qt::LeftToRight);
        label_additional->setStyleSheet(QString::fromUtf8("QLabel {\n"
"  qproperty-alignment: 'AlignVCenter | AlignRight';\n"
"  border: 1px solid gray;\n"
"}\n"
"background-color : white;"));
        label_additional->setScaledContents(false);
        label_additional->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_additional->setMargin(8);
        label_activate = new QPushButton(centralwidget);
        label_activate->setObjectName(QString::fromUtf8("label_activate"));
        label_activate->setGeometry(QRect(30, 30, 701, 71));
        label_activate->setStyleSheet(QString::fromUtf8("background-color: transparent; border: 0px"));
        label_x = new QLabel(centralwidget);
        label_x->setObjectName(QString::fromUtf8("label_x"));
        label_x->setEnabled(false);
        label_x->setGeometry(QRect(573, 12, 151, 16));
        label_x_activate = new QPushButton(centralwidget);
        label_x_activate->setObjectName(QString::fromUtf8("label_x_activate"));
        label_x_activate->setGeometry(QRect(545, 10, 186, 20));
        label_x_activate->setStyleSheet(QString::fromUtf8("background-color: transparent; border: 0px"));
        MainWindow->setCentralWidget(centralwidget);
        label_result->raise();
        label_additional->raise();
        label_size_2->raise();
        layoutWidget->raise();
        label_size->raise();
        label->raise();
        label_activate->raise();
        label_x->raise();
        label_x_activate->raise();
#if QT_CONFIG(shortcut)
        label_result->setBuddy(label_result);
        label_additional->setBuddy(label_result);
#endif // QT_CONFIG(shortcut)

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_size_2->setText(QCoreApplication::translate("MainWindow", "/255", nullptr));
#if QT_CONFIG(tooltip)
        butt_fn_asin->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>asin(</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        butt_fn_asin->setText(QCoreApplication::translate("MainWindow", "asin", nullptr));
        butt_bracket_op->setText(QCoreApplication::translate("MainWindow", "(", nullptr));
#if QT_CONFIG(shortcut)
        butt_bracket_op->setShortcut(QCoreApplication::translate("MainWindow", "(", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        butt_fn_tan->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>tan(</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        butt_fn_tan->setText(QCoreApplication::translate("MainWindow", "tan", nullptr));
#if QT_CONFIG(shortcut)
        butt_fn_tan->setShortcut(QCoreApplication::translate("MainWindow", "T", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_mode_deposit->setText(QCoreApplication::translate("MainWindow", "deposit", nullptr));
#if QT_CONFIG(shortcut)
        butt_mode_deposit->setShortcut(QCoreApplication::translate("MainWindow", "D", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_num_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
#if QT_CONFIG(shortcut)
        butt_num_4->setShortcut(QCoreApplication::translate("MainWindow", "4", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_percent->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
#if QT_CONFIG(tooltip)
        butt_fn_atan->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>atan(</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        butt_fn_atan->setText(QCoreApplication::translate("MainWindow", "atan", nullptr));
        butt_num_0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
#if QT_CONFIG(shortcut)
        butt_num_0->setShortcut(QCoreApplication::translate("MainWindow", "0", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_num_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
#if QT_CONFIG(shortcut)
        butt_num_2->setShortcut(QCoreApplication::translate("MainWindow", "2", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_op_result->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
#if QT_CONFIG(shortcut)
        butt_op_result->setShortcut(QCoreApplication::translate("MainWindow", "Return", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_fn_op_x->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
#if QT_CONFIG(shortcut)
        butt_fn_op_x->setShortcut(QCoreApplication::translate("MainWindow", "X", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_bracket_cl->setText(QCoreApplication::translate("MainWindow", ")", nullptr));
#if QT_CONFIG(shortcut)
        butt_bracket_cl->setShortcut(QCoreApplication::translate("MainWindow", ")", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_num_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
#if QT_CONFIG(shortcut)
        butt_num_6->setShortcut(QCoreApplication::translate("MainWindow", "6", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_num_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
#if QT_CONFIG(shortcut)
        butt_num_1->setShortcut(QCoreApplication::translate("MainWindow", "1", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        butt_degree->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>^</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        butt_degree->setText(QCoreApplication::translate("MainWindow", "x^y", nullptr));
#if QT_CONFIG(shortcut)
        butt_degree->setShortcut(QCoreApplication::translate("MainWindow", "\\", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        butt_fn_cos->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>cos(</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        butt_fn_cos->setText(QCoreApplication::translate("MainWindow", "cos", nullptr));
#if QT_CONFIG(shortcut)
        butt_fn_cos->setShortcut(QCoreApplication::translate("MainWindow", "C", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_op_mul->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
#if QT_CONFIG(shortcut)
        butt_op_mul->setShortcut(QCoreApplication::translate("MainWindow", "*", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_mod->setText(QCoreApplication::translate("MainWindow", "mod", nullptr));
#if QT_CONFIG(shortcut)
        butt_mod->setShortcut(QCoreApplication::translate("MainWindow", "M", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        butt_sq_root->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\342\210\232(</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        butt_sq_root->setText(QCoreApplication::translate("MainWindow", "root", nullptr));
#if QT_CONFIG(shortcut)
        butt_sq_root->setShortcut(QCoreApplication::translate("MainWindow", "R", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_op_sub->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
#if QT_CONFIG(shortcut)
        butt_op_sub->setShortcut(QCoreApplication::translate("MainWindow", "-", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        butt_fn_sin->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>sin(</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        butt_fn_sin->setText(QCoreApplication::translate("MainWindow", "sin", nullptr));
#if QT_CONFIG(shortcut)
        butt_fn_sin->setShortcut(QCoreApplication::translate("MainWindow", "S", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_op_sum->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
#if QT_CONFIG(shortcut)
        butt_op_sum->setShortcut(QCoreApplication::translate("MainWindow", "+", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_point->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
#if QT_CONFIG(shortcut)
        butt_point->setShortcut(QCoreApplication::translate("MainWindow", ".", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_num_9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
#if QT_CONFIG(shortcut)
        butt_num_9->setShortcut(QCoreApplication::translate("MainWindow", "9", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_num_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
#if QT_CONFIG(shortcut)
        butt_num_7->setShortcut(QCoreApplication::translate("MainWindow", "7", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_num_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
#if QT_CONFIG(shortcut)
        butt_num_3->setShortcut(QCoreApplication::translate("MainWindow", "3", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        butt_log->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>log(</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        butt_log->setText(QCoreApplication::translate("MainWindow", "log", nullptr));
#if QT_CONFIG(shortcut)
        butt_log->setShortcut(QCoreApplication::translate("MainWindow", "L", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_mode_graph->setText(QCoreApplication::translate("MainWindow", "graph", nullptr));
#if QT_CONFIG(tooltip)
        butt_fn_acos->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>acos(</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        butt_fn_acos->setText(QCoreApplication::translate("MainWindow", "acos", nullptr));
#if QT_CONFIG(tooltip)
        butt_ln->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>ln(</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        butt_ln->setText(QCoreApplication::translate("MainWindow", "ln", nullptr));
#if QT_CONFIG(shortcut)
        butt_ln->setShortcut(QCoreApplication::translate("MainWindow", "Backspace, Backspace, Backspace", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_ac->setText(QCoreApplication::translate("MainWindow", "AC", nullptr));
#if QT_CONFIG(shortcut)
        butt_ac->setShortcut(QCoreApplication::translate("MainWindow", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_num_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
#if QT_CONFIG(shortcut)
        butt_num_8->setShortcut(QCoreApplication::translate("MainWindow", "8", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_num_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
#if QT_CONFIG(shortcut)
        butt_num_5->setShortcut(QCoreApplication::translate("MainWindow", "5", nullptr));
#endif // QT_CONFIG(shortcut)
        butt_mode_credit->setText(QCoreApplication::translate("MainWindow", "credit", nullptr));
        butt_op_div->setText(QCoreApplication::translate("MainWindow", "\303\267", nullptr));
#if QT_CONFIG(shortcut)
        butt_op_div->setShortcut(QCoreApplication::translate("MainWindow", "/", nullptr));
#endif // QT_CONFIG(shortcut)
        label_result->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:18pt;\">0</span></p></body></html>", nullptr));
        label_size->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "x =", nullptr));
        label_additional->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
        label_activate->setText(QString());
        label_x->setText(QString());
        label_x_activate->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
