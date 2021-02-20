#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication awer(argc, argv);
    MainWindow w;
    w.show();
    return awer.exec();


}
