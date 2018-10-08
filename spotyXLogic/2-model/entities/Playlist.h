#ifndef Playlist_H
#define Playlist_H
#include <QString>
#include <memory>
#include <vector>
#include "Music.h"
using namespace std;
namespace model {
    class Playlist{
    public:
        int id;
        int idUser;
        QString name;
        unique_ptr<vector<shared_ptr<model::Music>>> musics;
        Playlist();
        Playlist(int idUser, QString name);
        Playlist(int id, int idUser, QString name);
    };
}
#endif
