#include "playlist.h"
model::Playlist::Playlist()
{
    this->id = -1;
}

model::Playlist::Playlist(int idUser, QString name)
{
    this->id = -1;
    this->name = name;
    this->idUser = idUser;
}

model::Playlist::Playlist(int id, int idUser, QString name)
{
    this->id = id;
    this->name = name;
    this->idUser = idUser;

}
