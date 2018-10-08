#include "UserDataFetcher.h"

#include <QNetworkRequest>
#include <QUrl>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QtDebug>
#include <QJsonDocument>
#include <QJsonObject>
infra::UserDataFetcher::UserDataFetcher(QObject *obj):
    QObject (obj)
{

}

QString infra::UserDataFetcher::getName(QString accessToken)
{
    QUrl url("https://api.spotify.com/v1/me");
    QNetworkRequest request(url);
    QByteArray authKey;
    authKey.append("Authorization");
    QByteArray authVal;
    authVal.append("Bearer ");
    authVal.append(accessToken);
    request.setRawHeader(authKey, authVal);
    //ritual da rede
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QNetworkReply* reply = networkManager->get(request);
    QEventLoop loop;
    loop.connect(networkManager, SIGNAL(finished(QNetworkReply*)), SLOT(quit()));
    loop.exec();
    QByteArray data = reply->readAll();//os dados tão aqui
    qDebug(data);
    //pegar o json
    QJsonObject rootObject = QJsonDocument::fromJson(data).object();
    QString name = rootObject.value("display_name").toString();
    return name;
}
