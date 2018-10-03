#include "AuthenticationServer.h"
#include <string>
infra::AuthenticationServer::AuthenticationServer(QString stateString, QObject *parent)
    :HttpRequestHandler (parent),
     stateString(stateString)
{

}

infra::AuthenticationServer::~AuthenticationServer()
{

}

void infra::AuthenticationServer::service(HttpRequest &req, HttpResponse &resp)
{
    //os params da req
    auto params = req.getParameterMap();
    //Pega o code.
    auto codeIterator = params.find("code");
    QString code;
    while (codeIterator!=params.end() && codeIterator.key()=="code") {
        code = codeIterator.value();
        ++codeIterator;
    }
    //pega o state.
    auto stateIterator = params.find("state");
    QString state;
    while (stateIterator!=params.end() && codeIterator.key()=="state") {
        state = stateIterator.value();
        ++stateIterator;
    }
    //pega o metodo
    std::string whatMethod = req.getMethod().toStdString();
    if(whatMethod=="GET" && state==stateString)
    {
        //eu tenho o code, hora de mandar o sinal de ter código.
        emit codeArrived(code);
    }
}
