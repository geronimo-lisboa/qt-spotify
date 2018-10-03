#include "AuthenticationPage.h"

infra::AuthenticationPage::AuthenticationPage(QString clientId,QString stateString, QObject *parent):
    QObject(parent), stateString(stateString), clientId(clientId)
{
    view = new QWebEngineView();
}

void infra::AuthenticationPage::show()
{
    QUrl url("https://accounts.spotify.com/authorize");
    QUrlQuery query;
    query.addQueryItem("client_id", clientId);
    query.addQueryItem("response_type", "code");
    query.addQueryItem("redirect_uri", "http%3A%2F%2Flocalhost:15000");
    query.addQueryItem("state", stateString);
    query.addQueryItem("scope", "user-read-private");
    url.setQuery(query.query());
    view->setUrl(url);
    view->resize(600,600);
    view->show();
}

infra::AuthenticationPage::~AuthenticationPage()
{
    delete view;
}

void infra::AuthenticationPage::close()
{
    view->close();
}
