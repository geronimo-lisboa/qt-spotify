#ifndef AuthenticationService_h
#define AuthenticationService_h
#include <QtCore>
#include <memory>
#include <QtCore/qglobal.h>
#include <3-infra/authenticaton/AuthenticationDTO.h>
namespace stefanfrings{
    class HttpListener;
}
namespace infra {
    class AuthenticationServer;
    class AuthenticationPage;
}


namespace model {
////Classe responsável pela autenticação do usuário. O usuário precisa
/// acessar a página do spotify pra conseguir autenticar. Essa classe
/// começa o processo de autenticação no método beginAuthentication() e
/// o resultado da autenticação, o CODE do usuário, será informado aos
/// interessados no sinal authenticationSuccessful
    class AuthenticationService : public QObject
    {
        Q_OBJECT
    private:
        QString clientId;
        QString stateString;
        stefanfrings::HttpListener* httpListener;
        std::unique_ptr<infra::AuthenticationPage> authenticationPage;
        std::unique_ptr<infra::AuthenticationServer> authenticationServer;
    public:
        AuthenticationService(QObject* parent=nullptr);
        ~AuthenticationService();
        infra::AuthenticationDTO getAcessAndRefreshTokens(QString code);
        void beginAuthentication();
    private slots:
        void authenticationSuccessfulSlot(QString code);
    signals:
        void authenticationSuccessful(infra::AuthenticationDTO authDto);
    };
}
#endif
