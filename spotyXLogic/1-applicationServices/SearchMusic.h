#ifndef SearchMusic_h
#define SearchMusic_h
#include <QString>
#include <memory>
#include <2-model/MusicService.h>
using namespace std;
namespace model {

    class User;
    class Music;
}
namespace applicationServices {
    class SearchMusic{
    public:
        SearchMusic();
        unique_ptr<vector<shared_ptr<model::Music>>> searchMusic(QString query, shared_ptr<model::User> user);
    private:
        unique_ptr<model::MusicService> musicService;
    };
}
#endif
