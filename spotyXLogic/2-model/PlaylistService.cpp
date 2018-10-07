#include "PlaylistService.h"
#include <3-infra/repository/PlaylistRepository.h>
#include <2-model/entities/Playlist.h>
#include <3-infra/repository/DatabaseManager.h>

model::PlaylistService::PlaylistService():
    playlistRepository( infra::DatabaseManager::instance().getPlaylistRepository() )
{

}

void model::PlaylistService::createNew(shared_ptr<model::Playlist> p)
{
    playlistRepository->addPlaylist(p);
}
