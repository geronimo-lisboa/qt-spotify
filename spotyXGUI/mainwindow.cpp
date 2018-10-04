#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <spotyxlogic.h>
#include <2-model/AuthenticationService.h>
#include <2-model/UserService.h>
#include <2-model/entities/User.h>
#include <vector>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //instancia o userservice
    userService = std::make_unique<model::UserService>();
    connect(ui->btnTesteUserSevice, &QPushButton::pressed,
            this,&MainWindow::testeUserService);

    //instancia o authenticationService
    model::AuthenticationService* authService = new model::AuthenticationService(this);
    connect(authService,
            &model::AuthenticationService::authenticationSuccessful,
            this,
            [this](infra::AuthenticationDTO authDto){
            qDebug("o dto está aqui?");
    });

    connect(ui->btn, &QPushButton::pressed, this, [authService](){
       authService->beginAuthentication();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::testeUserService()
{
    std::shared_ptr<model::User> user = std::make_shared<model::User>("code","foobar");
    const int sz0 = userService->getUsers()->size();
    userService->addUser(user);
    const int sz1 = userService->getUsers()->size();
    assert(sz0+1 == sz1);
    auto createdUser = userService->getUser(user->getId());
    assert(*createdUser == *user);
}
