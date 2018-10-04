#ifndef User_h
#define User_h
#include <QString>
#include "2-model/entities/UserSpotifyData.h"
#include <memory>
using namespace std;
namespace model
{
////É o meu usuário
    class User
    {
    private:
         int id;
        QString code;
        QString name;
        shared_ptr<UserSpotifyData> spotifyData;
    public:
        const static int INVALID_ID = -1;
        User(QString code, QString name, int id);
        User(QString code, QString name);
        QString getCode();
        void setCode(QString code);
        QString getName();
        void setName(QString name);
        int getId();
        void setId(int id);
        shared_ptr<UserSpotifyData> getSpotifyData();
        void setSpotifyData(shared_ptr<UserSpotifyData> d);
        bool operator==(const User& b);
    };
}
#endif
