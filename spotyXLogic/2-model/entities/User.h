#ifndef User_h
#define User_h
#include <QString>
#include "2-model/entities/UserSpotifyData.h"
#include <memory>
#include <vector>
using namespace std;
namespace model
{
    class Playlist;
////É o meu usuário
    class User
    {
    private:
         int id;
        QString code;
        QString name;
        shared_ptr<UserSpotifyData> spotifyData;
        unique_ptr<vector<shared_ptr<Playlist>>> playlists;
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

        void setPlaylists(unique_ptr<vector<shared_ptr<Playlist>>> p);
        vector<shared_ptr<Playlist>>* getPlaylist();

        bool operator==(const User& b);
    };
}
#endif
