#ifndef MusicService_h
#define MusicService_h
#include <QString>
#include <memory>
#include <3-infra/MusicFetcher.h>
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
    private:
        unique_ptr<infra::MusicFetcher> musicFetcher;
    };
}
#endif
