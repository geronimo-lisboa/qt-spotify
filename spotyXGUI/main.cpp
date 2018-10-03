#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <stdexcept>
#include <exceptions/IniFileNotPresentException.h>
#include <exceptions/exceptionBox.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try {
        MainWindow w;
        w.show();
        return a.exec();
    } catch (IniFileNotPresentException& ex) {
        showExceptionBox(ex);
        return EXIT_FAILURE;
    }
}

