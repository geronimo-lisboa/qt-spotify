#include "TokenRefresh.h"
#include "3-infra/authenticaton/AuthenticationDTO.h"

#include <QNetworkRequest>
#include <QUrl>
infra::TokenRefresh::TokenRefresh()
{

}

infra::AuthenticationDTO infra::TokenRefresh::refresh(QString oldRefreshToken)
{
    QUrl url("https://accounts.spotify.com/api/token");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    return AuthenticationDTO();
}
