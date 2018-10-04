#include "AuthenticationService.h"
#include <QSettings>
#include "3-infra/AuthenticationServer.h"
#include "3-infra/AuthenticationPage.h"
#include "httplistener.h"
#include <string>
#include <sstream>
#include <QWebEngineView>
#include <QDebug>
#include <QFileInfo>
#include "exceptions/IniFileNotPresentException.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <3-infra/authenticaton/AuthenticationDTO.h>
using namespace stefanfrings;

QString base64_encode(QString string){
    QByteArray ba;
    ba.append(string);
    return ba.toBase64();
}

model::AuthenticationService::AuthenticationService(QObject *parent)
    :QObject(parent)
{
    QFileInfo checkFile(INI_FILE_PATH);
    if(!checkFile.exists() || !checkFile.isFile())
    {
        qDebug(INI_FILE_PATH);
        throw IniFileNotPresentException();
    }
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

infra::AuthenticationDTO model::AuthenticationService::getAcessAndRefreshTokens(QString code)
{
    //a url de pegar os tokens
    QUrl url("https://accounts.spotify.com/api/token");
    //montagem do request, tem que ir via dados de form no post
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray payload;
    payload.append("grant_type=");payload.append("authorization_code");
    payload.append("&");
    payload.append("code=");payload.append(code);
    payload.append("&");
    payload.append("redirect_uri=");payload.append("http%3A%2F%2Flocalhost:15000");//TODO: isso aqui devia virar uma constante global
    payload.append("&");
    payload.append("client_id=");payload.append("568f5c57cd48447eb8c59fafde9f1d34");//TODO: isso aqui devia virar uma constante global
    payload.append("&");
    payload.append("client_secret=");payload.append("43131196b0fa4885aa4ae9338cf4c961");//TODO: isso aqui devia virar uma constante global
    //Ritual para fazer a requisição de maneira síncrona.
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QNetworkReply* reply = networkManager->post(request, payload);
    QEventLoop loop;
    loop.connect(networkManager, SIGNAL(finished(QNetworkReply*)), SLOT(quit()));
    loop.exec();
    QByteArray data = reply->readAll();//os dados tão aqui
    //monta o json
    QJsonObject rootObject = QJsonDocument::fromJson(data).object();
    infra::AuthenticationDTO authenticationDto;
    authenticationDto.code = code;
    authenticationDto.accessToken = rootObject.value("access_token").toString();
    authenticationDto.tokenType = rootObject.value("token_type").toString();
    authenticationDto.scope = rootObject.value("scope").toString();
    authenticationDto.expiresIn = rootObject.value("expires_in").toInt();
    authenticationDto.refreshToken = rootObject.value("refresh_token").toString();
    //agora é mandar o dto pra fora
    return authenticationDto;
}

void model::AuthenticationService::beginAuthentication()
{
    authenticationPage->show();
}

void model::AuthenticationService::authenticationSuccessfulSlot(QString code)
{
    //fecha a janela de autenticação
    authenticationPage->close();
    //agora é hora de pedir o access e refresh tokens
    auto dto = this->getAcessAndRefreshTokens(code);
    //emite o sinal
    emit authenticationSuccessful(dto);
}
