#ifndef PlaylistRepository_h
#define PlaylistRepository_h
#include <vector>
#include <memory>
using namespace std;
class QSqlDatabase;
namespace model {
    class Playlist;
    class User;
}
namespace infra {
    class PlaylistRepository
    {
    private:
        QSqlDatabase& database;
    public:
        typedef vector<shared_ptr<model::Playlist>> ListOfPlaylists;
        PlaylistRepository(QSqlDatabase& db);
        void init()const;
        void addPlaylist(shared_ptr<model::Playlist> p)const;
        void updatePlaylist(shared_ptr<model::Playlist> p)const;
        unique_ptr<ListOfPlaylists> getPlaylists()const;
        unique_ptr<ListOfPlaylists> getPlaylists(shared_ptr<model::User> usu)const;
    };

}
#endif
