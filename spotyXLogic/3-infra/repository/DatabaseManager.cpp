#include "3-infra/repository/DatabaseManager.h"
#include <QSqlDatabase>
#include "3-infra/repository/UserRepository.h"

infra::DatabaseManager &infra::DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

std::shared_ptr<infra::UserRepository> infra::DatabaseManager::getUserRepository()
{
    return this->userRepository;
}

infra::DatabaseManager::~DatabaseManager()
{
    mDatabase->close();
    delete mDatabase;
}

infra::DatabaseManager::DatabaseManager(const QString &path):
    mDatabase(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")))
{
    mDatabase->setDatabaseName(path);
    mDatabase->open();
    userRepository = std::make_shared<UserRepository>(*mDatabase);
    userRepository->init();
}

