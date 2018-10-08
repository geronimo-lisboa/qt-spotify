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
    class Music;
    class MusicService;
}
namespace applicationServices {
    class ManagePlaylist
    {
    private:
        unique_ptr<model::PlaylistService> playlistService;
        unique_ptr<model::MusicService> musicService;
    public:
        ManagePlaylist();
        shared_ptr<model::Playlist> createNew(QString name, shared_ptr<model::User> user);

        shared_ptr<model::Playlist> chooseInitialPlaylist(shared_ptr<model::User> user);

        void addMusicToPlaylist(shared_ptr<model::Playlist> playlist, shared_ptr<model::Music> music);
    };
}
#endif
