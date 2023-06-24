#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtWidgets/qlabel.h"
#include <QMainWindow>
#include <QShortcut>
#include <string>

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


private slots:
    void activateLabelX();
    void activateLabel();
    void typeChars();
    void typeFunctions();
    void addSpace();
    void addESym();
    void deleteLastSym();
    void clearInput();
    void initGraph();
    void calculate();
};
} //namespace s21
#endif // MAINWINDOW_H
