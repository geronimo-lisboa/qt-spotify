#include "User.h"

model::User::User(QString code, QString name,  int id)
{
    this->code = code;
    this->name = name;
    this->id = id;
}

model::User::User(QString code, QString name)
{
    this->code = code;
    this->name = name;
    this->id = INVALID_ID;
}

QString model::User::getCode()
{
    return code;
}

void model::User::setCode(QString code)
{
    this->code = code;
}

QString model::User::getName()
{
    return this->name;
}

void model::User::setName(QString name)
{
    this->name = name;
}

int model::User::getId()
{
    return this->id;
}

void model::User::setId(int id)
{
    this->id = id;
}

shared_ptr<model::UserSpotifyData> model::User::getSpotifyData()
{
    return spotifyData;
}

void model::User::setSpotifyData(shared_ptr<model::UserSpotifyData> d)
{
    spotifyData = d;
}

void model::User::setPlaylists(unique_ptr<vector<shared_ptr<model::Playlist> > > p)
{
    this->playlists = move(p);
}

vector<shared_ptr<model::Playlist>> *model::User::getPlaylist()
{
    if(playlists==nullptr)
    {
        playlists = std::make_unique<vector<shared_ptr<model::Playlist>>>();
    }
    return playlists.get();
}

bool model::User::operator==(const model::User &b)
{
    bool x = (b.name == this->name) ;
    bool y = (b.id == this->id);
    return ( x && y );

}
