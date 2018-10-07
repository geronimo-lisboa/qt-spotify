#ifndef Playlist_H
#define Playlist_H
#include <QString>
namespace model {
    class Playlist{
    public:
        int id;
        int idUser;
        QString name;

        Playlist();
        Playlist(int idUser, QString name);
        Playlist(int id, int idUser, QString name);
    };
}
#endif
