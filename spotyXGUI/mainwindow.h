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
    class CreateUser;
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
    std::unique_ptr<applicationServices::CreateUser> createNewUserApplicationService;
    std::unique_ptr<std::vector<std::shared_ptr<model::User>>> users;
    std::unique_ptr<UserWindow> userWindow;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void btnOpenNewUserWindowPressed();
    //void successfulAuthentication(infra::AuthenticationDTO authDto);
    void successfulNewUserCreation(std::shared_ptr<model::User> user);
    void userDeniedPermission();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
