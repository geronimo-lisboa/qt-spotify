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

    class DatabaseManager
    {
    public:
        static DatabaseManager& instance();
        std::shared_ptr<UserRepository> getUserRepository();
        std::shared_ptr<UserSpotifyDataRepository> getUserSpotifyDataRepository();
        ~DatabaseManager();
    protected:
        std::shared_ptr<UserRepository> userRepository;
        std::shared_ptr<UserSpotifyDataRepository> userSpotifyDataRepository;
        DatabaseManager(const QString& path = DATABASE_FILENAME);
        DatabaseManager& operator=(const DatabaseManager& rhs);
    private:
        QSqlDatabase* mDatabase;
    };
}
#endif
