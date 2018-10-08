#include "EncodeClientIdClientSecret.h"
#include <QString>
#include <QByteArray>
QByteArray infra::EncodeClientIdClientSecret::encode(QString clientId, QString clientSecret)
{
    QString str = "Authorization: Basic "+clientId+":"+clientSecret;
    QByteArray buff = str.toUtf8();
    return buff.toBase64();
}
