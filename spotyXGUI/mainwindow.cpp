#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <spotyxlogic.h>
#include <2-model/AuthenticationService.h>
#include <2-model/UserService.h>
#include <2-model/entities/User.h>
#include <2-model/entities/UserSpotifyData.h>
#include <vector>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //instancia o authenticationService
    model::AuthenticationService* authService = new model::AuthenticationService(this);
    //------conexões de signals e slots-------
    //O resultado da autenticação
    connect(authService, &model::AuthenticationService::authenticationSuccessful,
            this, &MainWindow::successfulAuthentication);
    //botão de autenticacao
    connect(ui->btn, &QPushButton::pressed, this, [authService](){
       authService->beginAuthentication();
    });
    //criação do usuário de teste
    connect(ui->btnCriarUsuTeste, &QPushButton::pressed,
            this,[service=userService.get()](){
        std::shared_ptr<model::User> teste = make_shared<model::User>("n/d","Charles Bronson");
        service->addUser(teste);//com  isso terei o charles bronson.
    });
    ///-------------O RITUAL DO USUÁRIO----------------
    ///     //instancia o userservice
    userService = std::make_unique<model::UserService>();
    //carrega meu usuário de teste
    this->user = userService->getUser(4);
    //o usuário tem informação de spotify? se tiver atualiza o token. Se não tiver, vai ter q fazer a
    //autenticacao
    if(this->user->getSpotifyData()!=nullptr)
    {
        userService->refreshToken(user);
    }
    else
    {
        authService->beginAuthentication();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::successfulAuthentication(infra::AuthenticationDTO authDto)
{
    //ligar o authDTO ao meu usuário
    std::shared_ptr<model::UserSpotifyData> sd = make_shared<model::UserSpotifyData>(authDto);
    userService->updateUserSpotifyData(user, sd);
    qDebug("ok?");
}

