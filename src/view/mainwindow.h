#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtWidgets/qlabel.h"
#include <QMainWindow>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui_;
    QLabel *label_;

private slots:
    void activateLabelX();
    void activateLabel();
    void typeChars();
    void typeFunctions();
    void deleteLastSym();
    void clearInput();
    void initGraph();
};
#endif // MAINWINDOW_H
