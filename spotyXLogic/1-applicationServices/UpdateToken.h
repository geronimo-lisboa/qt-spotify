#ifndef UpdateToken_h
#define UpdateToken_h
#include <QtCore>
#include <memory>
using namespace std;
namespace model{
    class User;
    class UserService;
}

namespace applicationServices {
    class UpdateToken : public QObject{
        Q_OBJECT
    public:
        UpdateToken(QObject* obj, shared_ptr<model::User> user);
    public slots:
        void Refresh();
    private:
        shared_ptr<model::User> user;
        unique_ptr<model::UserService> userService;

    };
}
#endif
