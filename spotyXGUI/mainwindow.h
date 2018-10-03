#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
namespace Ui {
class MainWindow;
}

namespace model {
    class UserService;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    std::unique_ptr<model::UserService> userService;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void testeUserService();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
