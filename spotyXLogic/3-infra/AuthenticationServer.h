#ifndef AuthenticationServer_h
#define AuthenticationServer_h
#include "httprequesthandler.h"
using namespace stefanfrings;
namespace infra
{
    class AuthenticationServer:public HttpRequestHandler
    {
        Q_OBJECT
        Q_DISABLE_COPY(AuthenticationServer)
    private:
        QString stateString;
    public:
        AuthenticationServer(QString stateString, QObject* parent = nullptr);
        ~AuthenticationServer()override;
        void service(HttpRequest &req, HttpResponse &resp)override;
    signals:
        void codeArrived(QString code);
        void accessDenied();
    };
}
#endif
