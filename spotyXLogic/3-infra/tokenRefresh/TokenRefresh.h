#ifndef TokenRefresh_h
#define TokenRefresh_h
#include <QString>
#include <QObject>
namespace infra {
    struct AuthenticationDTO;
    class TokenRefresh : public QObject{
        Q_OBJECT
    public:
        TokenRefresh(QObject *parent=nullptr);
        AuthenticationDTO refresh(QString oldRefreshToken);
    };
}
#endif
