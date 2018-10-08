#include "UserRepository.h"
#include "2-model/entities/User.h"
#include "2-model/entities/UserSpotifyData.h"
#include "3-infra/repository/UserSpotifyDataRepository.h"
#include "exceptions/SqlException.h"
#include <QSqlDatabase>
#include<QSqlQuery>
#include<QVariant>
#include<QStringList>
unique_ptr<model::User> infra::UserRepository::createFromQuery(QSqlQuery &query)const
{
    auto id = query.value("id").toInt();
    auto name = query.value("name").toString();
    auto code = query.value("code").toString();
    unique_ptr<model::User> u = make_unique<model::User>(code, name, id);
    return u;
}

infra::UserRepository::UserRepository(QSqlDatabase &db, shared_ptr<UserSpotifyDataRepository> spotifyRepo, shared_ptr<PlaylistRepository> playRepo):
    database(db),
    spotifyRepository(spotifyRepo),
    playlistRepository(playRepo)
{

}

void infra::UserRepository::purgeUsers() const
{
    QSqlQuery query(database);
    query.exec("DELETE FROM users");
}

void infra::UserRepository::init()const
{
    if(!database.tables().contains("users"))
    {
        QSqlQuery query(database);
        bool ok = query.exec("CREATE TABLE users "
                        "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "name TEXT NOT NULL,"
                        "code TEXT)");
        if(!ok)
        {
            throw SqlException();
        }
    }
}

void infra::UserRepository::addUser(std::shared_ptr<model::User> usu)const
{
    QSqlQuery query (database);
    query.prepare("INSERT INTO users "
                  "(name, code) "
                  "VALUES "
                  "( :name, :code)");
    query.bindValue(":name", usu->getName());
    query.bindValue(":code", usu->getCode());
    query.exec();
    usu->setId(query.lastInsertId().toInt());
}

void infra::UserRepository::updateUser(std::shared_ptr<model::User> usu)const
{
    QSqlQuery query(database);
    query.prepare("UPDATE users "
                  "SET name=:name, "
                  "code=:code "
                  "WHERE id=:id");
    query.bindValue(":name", usu->getName());
    query.bindValue(":code", usu->getCode());
    query.bindValue(":id", usu->getId());
    query.exec();
}

unique_ptr<infra::UserRepository::ListOfUsers> infra::UserRepository::getUsers()const
{
    unique_ptr<ListOfUsers> lst = make_unique<ListOfUsers>();
    QSqlQuery query("SELECT * FROM users", database);
    query.exec();
    while(query.next())
    {
        unique_ptr<model::User> u = createFromQuery(query);
        lst->push_back(move(u));
    }
    //Eu sei que o certo seria pegar a spotify data com um join mas to com pressa
    for_each(lst->begin(), lst->end(), [sr = spotifyRepository](shared_ptr<model::User> user){
        auto data = sr->getSpotifyData(*user);
        user->setSpotifyData(data);
    });
    //pega as listas de musica
    for_each(lst->begin(), lst->end(),[this, pr = playlistRepository](shared_ptr<model::User> user){
        auto playLists = playlistRepository->getPlaylists(user);
        user->setPlaylists(move(playLists));
    });
    return lst;
}

unique_ptr<infra::UserRepository::ListOfUsers> infra::UserRepository::getUsers(QString userName) const
{
    unique_ptr<ListOfUsers> lst = make_unique<ListOfUsers>();
    QSqlQuery query(database);
    query.prepare("SELECT * FROM users WHERE name=:name");
    query.bindValue(":name", userName);
    query.exec();
    while(query.next())
    {
        unique_ptr<model::User> u = createFromQuery(query);
        lst->push_back(move(u));
    }
    //Eu sei que o certo seria pegar a spotify data com um join mas to com pressa
    for_each(lst->begin(), lst->end(), [sr = spotifyRepository](shared_ptr<model::User> user){
        auto data = sr->getSpotifyData(*user);
        user->setSpotifyData(data);
    });
    //pega as listas de musica
    for_each(lst->begin(), lst->end(),[this, pr = playlistRepository](shared_ptr<model::User> user){
        auto lst = playlistRepository->getPlaylists(user);
        user->setPlaylists(move(lst));
    });
    return lst;

}

unique_ptr<infra::UserRepository::ListOfUsers> infra::UserRepository::getUsers(const int id) const
{
    unique_ptr<ListOfUsers> lst = make_unique<ListOfUsers>();
    QSqlQuery query(database);
    query.prepare("SELECT * FROM users WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();
    while(query.next())
    {
        unique_ptr<model::User> u = createFromQuery(query);
        lst->push_back(move(u));
    }
    //Eu sei que o certo seria pegar a spotify data com um join mas to com pressa
    for_each(lst->begin(), lst->end(), [sr = spotifyRepository](shared_ptr<model::User> user){
        auto data = sr->getSpotifyData(*user);
        user->setSpotifyData(data);
    });
    //pega as listas de musica
    for_each(lst->begin(), lst->end(),[this, pr = playlistRepository](shared_ptr<model::User> user){
        auto lst = playlistRepository->getPlaylists(user);
        user->setPlaylists(move(lst));
    });
    return lst;
}
