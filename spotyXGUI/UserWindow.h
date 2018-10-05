#ifndef USERWINDOW_H
#define USERWINDOW_H
#include <memory>
#include <QWidget>

using namespace std;

namespace Ui {
class UserWindow;
}

namespace model {
    class User;
}

class UserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UserWindow(shared_ptr<model::User> user,
                        QWidget *parent = nullptr);
    ~UserWindow();

private:
    Ui::UserWindow *ui;
    shared_ptr<model::User> user;
};

#endif // USERWINDOW_H
