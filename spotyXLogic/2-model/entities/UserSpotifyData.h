#ifndef UserSpotifyData_h
#define UserSpotifyData_h
#include <QString>
#include "3-infra/authenticaton/AuthenticationDTO.h"
namespace model {
    class UserSpotifyData{
    public:
        UserSpotifyData();
        UserSpotifyData(infra::AuthenticationDTO dto);
        UserSpotifyData(infra::AuthenticationDTO dto, int idUser, int id);
        ///Decidi por publico pq os getters e setters não fariam lógica alguma
        ///e eu estaria perdendo tempo.
        int idUser;
        int id;
        QString code;
        QString accessToken;
        QString tokenType;
        QString scope;
        int expiresIn;
        QString refreshToken;
        bool operator==(const UserSpotifyData& b);
    };
}
#endif
