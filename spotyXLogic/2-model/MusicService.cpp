#include "MusicService.h"
#include "2-model/entities/Music.h"
#include "2-model/entities/User.h"
#include "3-infra/MusicFetcher.h"
#include "3-infra/repository/DatabaseManager.h"
model::MusicService::MusicService():
    musicFetcher(new infra::MusicFetcher()),
    musicRepository(infra::DatabaseManager::instance().getMusicRepository())
{

}

unique_ptr<vector<shared_ptr<model::Music>>> model::MusicService::searchInSpotify(QString query, shared_ptr<User> user)
{
    return musicFetcher->search(query, user);
}

void model::MusicService::add(std::shared_ptr<model::Music> music)
{
    musicRepository->addMusic(music);
}
