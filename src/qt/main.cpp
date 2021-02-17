#include "mainwindow.hpp"

#include <QApplication>

#include "common.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    MainWindow w(argv);
    w.show();

    return a.exec();
}
