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
#include <1-applicationServices/ListUsers.h>
#include <1-applicationServices/CreateUser.h>
#include "UserWindow.h"

void MainWindow::btnOpenNewUserWindowPressed()
{
    this->createNewUserApplicationService->beginCreation();
    ////Alguma coisa tem que ser feita em resposta à criação do usuário
    /// Alguma coisa tem que ser feita em resposta ao fracasso.
}

void MainWindow::successfulNewUserCreation(std::shared_ptr<model::User> user)
{
    this->userWindow = make_unique<UserWindow>(user, nullptr);
    this->userWindow->show();
    this->hide();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    listUsersApplicationService(new applicationServices::ListUsers()),
    ui(new Ui::MainWindow)
{
    this->createNewUserApplicationService = make_unique<applicationServices::CreateUser>(this);
    ui->setupUi(this);
    this->users = listUsersApplicationService->getUserList();
    //monta a lista
    for_each(users->begin(), users->end(),[this](std::shared_ptr<model::User> currentUser){
        QPushButton* newButton = new QPushButton(this);
        newButton->setText(currentUser->getName());
        connect(newButton, &QPushButton::pressed,
                this,[usu = currentUser, this](){
            this->userWindow = make_unique<UserWindow>(usu, nullptr);
            this->userWindow->show();
            this->hide();
        });
        this->ui->centralWidget->layout()->addWidget(newButton);
    });
    //void newUserCreated(std::shared_ptr<model::User> user);
    connect(this->createNewUserApplicationService.get(), &applicationServices::CreateUser::newUserCreated,
            this, &MainWindow::successfulNewUserCreation);
    connect(ui->btnNewUser, &QPushButton::pressed,
            this, &MainWindow::btnOpenNewUserWindowPressed);

/////O PASSADO DISTANTE...
//    //instancia o authenticationService
//    model::AuthenticationService* authService = new model::AuthenticationService(this);
//    //------conexões de signals e slots-------
//    //O resultado da autenticação
//    connect(authService, &model::AuthenticationService::authenticationSuccessful,
//            this, &MainWindow::successfulAuthentication);
//    //botão de autenticacao
//    connect(ui->btn, &QPushButton::pressed, this, [authService](){
//       authService->beginAuthentication();
//    });
//    //criação do usuário de teste
//    connect(ui->btnCriarUsuTeste, &QPushButton::pressed,
//            this,[service=userService.get()](){
//        std::shared_ptr<model::User> teste = make_shared<model::User>("n/d","Charles Bronson");
//        service->addUser(teste);//com  isso terei o charles bronson.
//    });
//    ///-------------O RITUAL DO USUÁRIO----------------
//    ///     //instancia o userservice
//    userService = std::make_unique<model::UserService>();
//    //carrega meu usuário de teste
//    this->user = userService->getUser(4);
//    //o usuário tem informação de spotify? se tiver atualiza o token. Se não tiver, vai ter q fazer a
//    //autenticacao
//    if(this->user->getSpotifyData()!=nullptr)
//    {
//        userService->refreshToken(user);
//    }
//    else
//    {
//        authService->beginAuthentication();
//    }

}

MainWindow::~MainWindow()
{
    delete ui;
}



//void MainWindow::successfulAuthentication(infra::AuthenticationDTO authDto)
//{
////// O PASSADO DISTANTE
////    //ligar o authDTO ao meu usuário
////    std::shared_ptr<model::UserSpotifyData> sd = make_shared<model::UserSpotifyData>(authDto);
////    userService->updateUserSpotifyData(user, sd);
////    qDebug("ok?");
//}

