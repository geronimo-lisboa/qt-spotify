#ifndef UserRepository_h
#define UserRepository_h
#include <vector>
#include <memory>
#include <QString>
#include "3-infra/repository/UserSpotifyDataRepository.h"
#include "3-infra/repository/PlaylistRepository.h"
//forward declarations
class QSqlDatabase;
class QSqlQuery;
namespace model
{
    class User;
}
using namespace std;
namespace infra
{
    class UserRepository
    {
    private:
        QSqlDatabase& database;
        shared_ptr<UserSpotifyDataRepository> spotifyRepository;
        shared_ptr<PlaylistRepository> playlistRepository;
        unique_ptr<model::User> createFromQuery(QSqlQuery& query)const;
    public:
        typedef vector<shared_ptr<model::User>> ListOfUsers;
        UserRepository(QSqlDatabase& db, shared_ptr<UserSpotifyDataRepository> spotifyRepo,
                       shared_ptr<PlaylistRepository> playRepo);
        //Todos os métodos dessa classe são stateless
        void init() const;
        void addUser(std::shared_ptr<model::User> usu) const;
        void updateUser(std::shared_ptr<model::User> usu) const;
        unique_ptr<ListOfUsers> getUsers()const;
        unique_ptr<ListOfUsers> getUsers(QString userName)const;
        unique_ptr<ListOfUsers> getUsers(const int id)const;
        void purgeUsers()const;
    };
}
#endif
