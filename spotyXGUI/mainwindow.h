#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <3-infra/authenticaton/AuthenticationDTO.h>

namespace Ui {
class MainWindow;
}

namespace applicationServices {
    class ListUsers;
}

namespace model {
    class UserService;
    class User;
}
class UserWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    std::unique_ptr<applicationServices::ListUsers> listUsersApplicationService;
    std::unique_ptr<std::vector<std::shared_ptr<model::User>>> users;
    std::unique_ptr<UserWindow> userWindow;
////O PASSADO DISTANTE
//    std::unique_ptr<model::UserService> userService;
//    std::shared_ptr<model::User> user;    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void successfulAuthentication(infra::AuthenticationDTO authDto);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
