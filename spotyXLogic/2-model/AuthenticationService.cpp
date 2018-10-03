#include "AuthenticationService.h"
#include <QSettings>
#include "3-infra/AuthenticationServer.h"
#include "3-infra/AuthenticationPage.h"
#include "httplistener.h"
#include <string>
#include <sstream>
#include <QWebEngineView>
using namespace stefanfrings;



model::AuthenticationService::AuthenticationService(QObject *parent)
    :QObject(parent)
{
    stateString = QString::fromStdString( "ixiquicaca" );
    //Cria o servidor pra onde o spotify vai mandar o código
    QSettings* listenerSettings = new QSettings(INI_FILE_PATH, QSettings::IniFormat, this);
    listenerSettings->beginGroup("listener");
    clientId = listenerSettings->value("clientId").toString();
    authenticationServer = std::make_unique<infra::AuthenticationServer>(stateString,this);
    httpListener = new HttpListener(listenerSettings,
                                   authenticationServer.get(),
                                   this);
    //Cria o objeto que guardará a página web do spotify
    authenticationPage = std::make_unique<infra::AuthenticationPage>(clientId, stateString, this);
    //liga ao sinal do servidor
    connect(authenticationServer.get(), &infra::AuthenticationServer::codeArrived,
            this, &AuthenticationService::authenticationSuccessfulSlot);
}

model::AuthenticationService::~AuthenticationService()
{

}

void model::AuthenticationService::beginAuthentication()
{
    authenticationPage->show();
}

void model::AuthenticationService::authenticationSuccessfulSlot(QString code)
{
    //fecha a janela de autenticação
    authenticationPage->close();
    //emite o sinal
    emit authenticationSuccessful(code);
}
