#ifndef CreateUser_h
#define CreateUser_h
#include <QtCore>
#include <memory>
#include <3-infra/authenticaton/AuthenticationDTO.h>
using namespace std;

namespace model {
    class UserService;
    class User;
    class AuthenticationService;
}


namespace applicationServices {
////O processo de criação de usuário. O processo começa em beginCreation()
/// mas termina no slot que trata o resultado da autenticacao;
    class CreateUser : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY(CreateUser)
    public:
        CreateUser(QObject* parent=nullptr);
        void beginCreation();
    public slots:
        void successfulAuthentication(infra::AuthenticationDTO authDto);
        void failerAuthentication();
    private:
        std::unique_ptr<model::UserService> userService;
        std::unique_ptr<model::AuthenticationService> authService;
        //std::shared_ptr<model::User> user;
    signals:
        void newUserCreated(std::shared_ptr<model::User> user);
    };
}
#endif
