#ifndef DatabaseManager_H
#define DatabaseManager_H
#include <QString>
#include <memory>
#include "UserRepository.h"
const QString DATABASE_FILENAME = "spoty.db";
class QSqlDatabase;

namespace infra
{
    class UserRepository;
    class UserSpotifyDataRepository;
    class PlaylistRepository;

    class DatabaseManager
    {
    public:
        static DatabaseManager& instance();
        std::shared_ptr<UserRepository> getUserRepository();
        std::shared_ptr<UserSpotifyDataRepository> getUserSpotifyDataRepository();
        std::shared_ptr<PlaylistRepository> getPlaylistRepository();
        ~DatabaseManager();
    protected:
        std::shared_ptr<UserRepository> userRepository;
        std::shared_ptr<UserSpotifyDataRepository> userSpotifyDataRepository;
        std::shared_ptr<PlaylistRepository> playlistRepository;
        DatabaseManager(const QString& path = DATABASE_FILENAME);
        DatabaseManager& operator=(const DatabaseManager& rhs);
    private:
        QSqlDatabase* mDatabase;
    };
}
#endif
