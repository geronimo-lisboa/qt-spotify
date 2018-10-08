#include "1-applicationServices/ManagePlaylist.h"
#include <2-model/entities/Playlist.h>
#include <2-model/PlaylistService.h>
#include <QString>
#include <2-model/entities/User.h>
#include "2-model/entities/Music.h"
#include "2-model/MusicService.h"
applicationServices::ManagePlaylist::ManagePlaylist():
    playlistService(new model::PlaylistService()),
    musicService(new model::MusicService())
{

}

shared_ptr<model::Playlist> applicationServices::ManagePlaylist::createNew(QString name, shared_ptr<model::User> user)
{
    //cria a playlist e a retorna
    std::shared_ptr<model::Playlist> playlist = make_shared<model::Playlist>(user->getId(), name);
    // unique_ptr<vector<shared_ptr<model::Music>>>
    playlist->musics = make_unique<vector<shared_ptr<model::Music>>>();
    playlistService->createNew(playlist);
    user->getPlaylist()->push_back(playlist);
    return  playlist;
}

shared_ptr<model::Playlist> applicationServices::ManagePlaylist::chooseInitialPlaylist(shared_ptr<model::User> user)
{
    ///dummy
    /// poderia estar vindo do banco, guardando qual foi a ultima que o cara ouviu
    if(user->getPlaylist()!=nullptr && user->getPlaylist()->size() > 0)
    {
        return (*(user->getPlaylist()))[0];
    }
    else
        return nullptr;
}

void applicationServices::ManagePlaylist::addMusicToPlaylist(shared_ptr<model::Playlist> playlist,
                                                             shared_ptr<model::Music> music)
{
    assert(playlist != nullptr &&"PLAYLIST N PODE SER NULL");
    assert(music != nullptr && "MUSIC N PODE SER NULL");
    music->idPlaylist = playlist->id;
    musicService->add(music);
    if(playlist->musics==nullptr)
        playlist->musics = make_unique<vector<shared_ptr<model::Music>>>();
    playlist->musics->push_back(music);
}
