#ifndef ManagePlaylist_h
#define ManagePlaylist_h
#include <memory>
#include <2-model/PlaylistService.h>
class QString;
using namespace std;
namespace model {
    class User;
    class Playlist;
    class PlaylistService;
}
namespace applicationServices {
    class ManagePlaylist
    {
    private:
        unique_ptr<model::PlaylistService> playlistService;
    public:
        ManagePlaylist();
        shared_ptr<model::Playlist> createNew(QString name, shared_ptr<model::User> user);
    };
}
#endif
