#include "SearchMusic.h"
#include "2-model/MusicService.h"
#include "2-model/entities/Music.h"
applicationServices::SearchMusic::SearchMusic():
    musicService(new model::MusicService())
{

}

unique_ptr<vector<shared_ptr<model::Music>>> applicationServices::SearchMusic::searchMusic(QString query, shared_ptr<model::User> user)
{
    return musicService->searchInSpotify(query, user);
}
