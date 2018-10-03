#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <spotyxlogic.h>
#include <2-model/AuthenticationService.h>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model::AuthenticationService* authService = new model::AuthenticationService(this);
    connect(authService,
            &model::AuthenticationService::authenticationSuccessful,
            this,
            [this](QString code){
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Test", code,
                                              QMessageBox::Yes|QMessageBox::No);
                if (reply == QMessageBox::Yes) {
                  qDebug() << "Yes was clicked";
                  QApplication::quit();
                } else {
                  qDebug() << "Yes was *not* clicked";
                }

    });

    connect(ui->btn, &QPushButton::pressed, this, [authService](){
       authService->beginAuthentication();
    });

//    teste::Spotylibrary* testeObj = new teste::Spotylibrary(this);
//    connect(testeObj,
//            &teste::Spotylibrary::testSignal,
//            this,
//            [this](QString str){
//        QMessageBox::StandardButton reply;
//        reply = QMessageBox::question(this, "Test", str,
//                                      QMessageBox::Yes|QMessageBox::No);
//        if (reply == QMessageBox::Yes) {
//          qDebug() << "Yes was clicked";
//          QApplication::quit();
//        } else {
//          qDebug() << "Yes was *not* clicked";
//        }
//    });
//    testeObj->foo();
}

MainWindow::~MainWindow()
{
    delete ui;
}
