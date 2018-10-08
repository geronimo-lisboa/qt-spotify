#include"PlaylistRepository.h"
#include <QStringList>
#include <QSqlError>
#include <2-model/entities/Playlist.h>
#include <2-model/entities/User.h>
#include <exceptions/SqlException.h>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <memory>
#include "3-infra/repository/MusicRepository.h"
infra::PlaylistRepository::PlaylistRepository(QSqlDatabase &db)
    :database(db)
{
    musicRepository = make_shared<infra::MusicRepository>(db);
}

void infra::PlaylistRepository::init() const
{
    if(!database.tables().contains("playlists"))
    {
        QSqlQuery query(database);
        bool ok = query.exec("CREATE TABLE playlists "
                        "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "idUser INTEGER, "
                        "name TEXT) "
        );
        if(!ok)
        {
            throw SqlException();
        }
    }
}

void infra::PlaylistRepository::addPlaylist(shared_ptr<model::Playlist> p) const
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO playlists "
                  "(idUser, name) "
                  "VALUES "
                  "(:idUser, :name)");
    query.bindValue(":idUser", p->idUser);
    query.bindValue(":name",p->name);
    bool ok = query.exec();

    p->id = query.lastInsertId().toInt();
}

void infra::PlaylistRepository::updatePlaylist(shared_ptr<model::Playlist> p) const
{
    QSqlQuery query(database);
    query.prepare(
                " UPDATE playlists "
                " SET "
                " idUser=:idUser,"
                " name=:name,"
                "WHERE id=:id"
                );
    query.bindValue(":idUser",p->idUser);
    query.bindValue(":name",p->name);
    query.bindValue(":id", p->id);
    bool ok = query.exec();
    if(!ok)
    {
        QString lastQuery = query.lastQuery();
        QString lastError = query.lastError().text();
        qDebug(lastQuery.toUtf8());
        qDebug(lastError.toUtf8());
    }
}

unique_ptr<infra::PlaylistRepository::ListOfPlaylists> infra::PlaylistRepository::getPlaylists() const
{
    QSqlQuery query(database);
    query.prepare("SELECT * FROM playlists");
    query.exec();
    auto lst = make_unique<ListOfPlaylists>();
    while (query.next()) {
        auto p = make_shared<model::Playlist>(query.value("id").toInt(), query.value("idUser").toInt(), query.value("name").toString());
        lst->push_back(p);
        auto musics = musicRepository->getMusic(p);
        p->musics = move(musics);
    }
    return lst;

}

unique_ptr<infra::PlaylistRepository::ListOfPlaylists> infra::PlaylistRepository::getPlaylists(shared_ptr<model::User> usu) const
{
    QSqlQuery query(database);
    query.prepare("SELECT * FROM playlists where idUser=:idUser");
    query.bindValue(":idUser", usu->getId());
    query.exec();
    auto lst = make_unique<ListOfPlaylists>();
    while (query.next()) {
        auto p = make_shared<model::Playlist>(query.value("id").toInt(), query.value("idUser").toInt(), query.value("name").toString());
        //pega as musicas
        lst->push_back(p);
        auto musics = musicRepository->getMusic(p);
        p->musics = move(musics);
    }
    return lst;

}
