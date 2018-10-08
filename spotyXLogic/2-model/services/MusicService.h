#ifndef MusicService_h
#define MusicService_h
#include <QString>
#include <memory>
#include <3-infra/fetch/MusicFetcher.h>
#include <3-infra/repository/MusicRepository.h>
using namespace std;
//namespace infra {
//    class MusicFetcher;
//}

namespace model {
    class User;
    class Music;

    class MusicService{
    public:
        MusicService();
        unique_ptr<vector<shared_ptr<model::Music>>> searchInSpotify(QString query, shared_ptr<User> user);
        void add(std::shared_ptr<model::Music> music);
    private:
        unique_ptr<infra::MusicFetcher> musicFetcher;
        shared_ptr<infra::MusicRepository> musicRepository;
    };
}
#endif
