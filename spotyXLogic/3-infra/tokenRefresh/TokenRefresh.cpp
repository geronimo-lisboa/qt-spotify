#include "TokenRefresh.h"
#include "3-infra/authenticaton/AuthenticationDTO.h"
#include "3-infra/PostContentBuilder.h"
#include "3-infra/EncodeClientIdClientSecret.h"
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <2-model/entities/User.h>
#include <2-model/entities/UserSpotifyData.h>
infra::TokenRefresh::TokenRefresh(QObject *parent):
    QObject (parent)
{

}

infra::AuthenticationDTO infra::TokenRefresh::refresh(model::User& user)
{
    QUrl url("https://accounts.spotify.com/api/token");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    PostContentBuilder postBuilder;
    postBuilder.add("grant_type","refresh_token");
    postBuilder.add("refresh_token",user.getSpotifyData()->refreshToken.toStdString());

    postBuilder.add("client_id","568f5c57cd48447eb8c59fafde9f1d34");
    postBuilder.add("client_secret","43131196b0fa4885aa4ae9338cf4c961");

    QByteArray postContent = postBuilder.getAssembled();

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QNetworkReply* reply = networkManager->post(request, postContent);
    QEventLoop loop;
    loop.connect(networkManager, SIGNAL(finished(QNetworkReply*)), SLOT(quit()));
    loop.exec();
    QByteArray data = reply->readAll();//os dados tão aqui
    //nessa resposta o refresh token nõa é atualizado, somente o access token, então devo montar o
    //meu dto de acordo
    //monta o json
    QJsonObject rootObject = QJsonDocument::fromJson(data).object();
    infra::AuthenticationDTO authenticationDto;
    authenticationDto.code = user.getSpotifyData()->code;
    authenticationDto.accessToken = rootObject.value("access_token").toString();
    authenticationDto.tokenType = rootObject.value("token_type").toString();
    authenticationDto.scope = rootObject.value("scope").toString();
    authenticationDto.expiresIn = rootObject.value("expires_in").toInt();
    authenticationDto.refreshToken = user.getSpotifyData()->refreshToken;

    qDebug("refresh de token");
    return authenticationDto;
}
