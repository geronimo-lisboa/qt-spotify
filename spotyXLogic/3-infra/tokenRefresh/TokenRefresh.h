#ifndef TokenRefresh_h
#define TokenRefresh_h
#include <QString>
namespace infra {
    class AuthenticationDTO;
    class TokenRefresh{
    public:
        TokenRefresh();
        AuthenticationDTO refresh(QString oldRefreshToken);
    };
}
#endif
