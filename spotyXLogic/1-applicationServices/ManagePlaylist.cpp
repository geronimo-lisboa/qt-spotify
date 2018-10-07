#include "1-applicationServices/ManagePlaylist.h"
#include <2-model/entities/Playlist.h>
#include <2-model/PlaylistService.h>
#include <QString>
#include <2-model/entities/User.h>
applicationServices::ManagePlaylist::ManagePlaylist():
    playlistService(new model::PlaylistService())
{

}

shared_ptr<model::Playlist> applicationServices::ManagePlaylist::createNew(QString name, shared_ptr<model::User> user)
{
    //cria a playlist e a retorna
    std::shared_ptr<model::Playlist> playlist = make_shared<model::Playlist>(user->getId(), name);
    playlistService->createNew(playlist);
    return  playlist;
}
