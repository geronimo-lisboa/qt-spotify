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

    class DatabaseManager
    {
    public:
        static DatabaseManager& instance();
        std::shared_ptr<UserRepository> getUserRepository();
        ~DatabaseManager();
    protected:
        std::shared_ptr<UserRepository> userRepository;
        DatabaseManager(const QString& path = DATABASE_FILENAME);
        DatabaseManager& operator=(const DatabaseManager& rhs);
    private:
        QSqlDatabase* mDatabase;
    };
}
#endif
