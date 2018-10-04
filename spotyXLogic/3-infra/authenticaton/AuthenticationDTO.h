#ifndef AuthenticationDTO_h
#define AuthenticationDTO_h
#include <QString>
namespace infra {
    struct AuthenticationDTO{
        QString code;
        QString accessToken;
        QString tokenType;
        QString scope;
        int expiresIn;
        QString refreshToken;
    };
}
#endif
