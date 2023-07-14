#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtWidgets/qlabel.h"
#include <QMainWindow>
#include <QShortcut>
#include <string>
#include "resources/qcustomplot.h"

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui_;
    QLabel *label_;
    Controller controller_;
    void scaleSpins(bool state);
    void initGraph();
    bool checkGraphFunc(const std::string &expr);

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
};
} //namespace s21
#endif // MAINWINDOW_H
