#include "view/credit_calc.h"
#include "view/main_calc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::MainCalc w;
    w.show();

    return a.exec();
}
