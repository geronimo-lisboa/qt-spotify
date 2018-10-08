#ifndef PlaylistService_h
#define PlaylistService_h
#include <memory>
using namespace std;
namespace infra {
    class PlaylistRepository;
}
namespace model {
    class Playlist;
    class PlaylistService
    {
    private:
        shared_ptr<infra::PlaylistRepository> playlistRepository;
    public:
        PlaylistService();
        void createNew(shared_ptr<Playlist> p);
    };
}
#endif
