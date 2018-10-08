#include "3-infra/repository/DatabaseManager.h"
#include <QSqlDatabase>
#include "3-infra/repository/UserRepository.h"
#include "3-infra/repository/UserSpotifyDataRepository.h"
#include "3-infra/repository/MusicRepository.h"
infra::DatabaseManager &infra::DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

std::shared_ptr<infra::UserRepository> infra::DatabaseManager::getUserRepository()
{
    return this->userRepository;
}

std::shared_ptr<infra::UserSpotifyDataRepository> infra::DatabaseManager::getUserSpotifyDataRepository()
{
    return this->userSpotifyDataRepository;
}

std::shared_ptr<infra::PlaylistRepository> infra::DatabaseManager::getPlaylistRepository()
{
    return this->playlistRepository;
}

std::shared_ptr<infra::MusicRepository> infra::DatabaseManager::getMusicRepository()
{
    return this->musicRepository;
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

    musicRepository = std::make_unique<MusicRepository>(*mDatabase);
    musicRepository->init();

    userSpotifyDataRepository = std::make_shared<UserSpotifyDataRepository>(*mDatabase);
    userSpotifyDataRepository->init();

    playlistRepository = std::make_shared<PlaylistRepository>(*mDatabase);
    playlistRepository->init();

    userRepository = std::make_shared<UserRepository>(*mDatabase,userSpotifyDataRepository, playlistRepository);
    userRepository->init();
}

