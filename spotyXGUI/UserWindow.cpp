#include "UserWindow.h"
#include "ui_UserWindow.h"

UserWindow::UserWindow(shared_ptr<model::User> user,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWindow),
    user(user)
{
    ui->setupUi(this);
}

UserWindow::~UserWindow()
{
    delete ui;
    QCoreApplication::quit();
}
