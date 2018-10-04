#include "TokenRefresh.h"
#include "3-infra/authenticaton/AuthenticationDTO.h"
#include "3-infra/PostContentBuilder.h"
#include "3-infra/EncodeClientIdClientSecret.h"
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
infra::TokenRefresh::TokenRefresh(QObject *parent):
    QObject (parent)
{

}

infra::AuthenticationDTO infra::TokenRefresh::refresh(QString oldRefreshToken)
{
    QUrl url("https://accounts.spotify.com/api/token");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    //QByteArray bAuthorization = QByteArray::fromStdString("Authorization");
    //infra::EncodeClientIdClientSecret encoder;
    //QByteArray encodedData = encoder.encode("568f5c57cd48447eb8c59fafde9f1d34","43131196b0fa4885aa4ae9338cf4c961");
    //request.setRawHeader(bAuthorization, encodedData);

    PostContentBuilder postBuilder;
    postBuilder.add("grant_type","refresh_token");
    postBuilder.add("refresh_token",oldRefreshToken.toStdString());

    postBuilder.add("client_id","568f5c57cd48447eb8c59fafde9f1d34");
    postBuilder.add("client_secret","43131196b0fa4885aa4ae9338cf4c961");

    QByteArray postContent = postBuilder.getAssembled();

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QNetworkReply* reply = networkManager->post(request, postContent);
    QEventLoop loop;
    loop.connect(networkManager, SIGNAL(finished(QNetworkReply*)), SLOT(quit()));
    loop.exec();
    QByteArray data = reply->readAll();//os dados tão aqui
    qDebug(data);

    return AuthenticationDTO();
}
