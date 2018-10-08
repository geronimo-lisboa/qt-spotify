#include "MusicRepository.h"
#include <QStringList>
#include <QSqlError>
#include <2-model/entities/Playlist.h>
#include <2-model/entities/Music.h>
#include <exceptions/SqlException.h>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <exceptions/SqlException.h>


infra::MusicRepository::MusicRepository(QSqlDatabase &db):
    database(db)
{

}

void infra::MusicRepository::init() const
{
    if(!database.tables().contains("musics"))
    {
        QSqlQuery query(database);
        bool ok = query.exec("CREATE TABLE musics "
                             "(id TEXT PRIMARY KEY, "
                             "idPlaylist INTEGER, "
                             "albumName TEXT, "
                             "artists TEXT, "
                             "name TEXT, "
                             "uri TEXT, "
                             "previewUrl TEXT)"
        );
        if(!ok)
        {
            QString lastQuery = query.lastQuery();
            QString lastError = query.lastError().text();
            qDebug(lastQuery.toUtf8());
            qDebug(lastError.toUtf8());
            throw SqlException();
        }
    }
}

void infra::MusicRepository::addMusic(shared_ptr<model::Music> m) const
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO musics "
                  "(id,idPlaylist, albumName, artists, name, uri, previewUrl) "
                  "VALUES "
                  "(:id, :idPlaylist, :albumName, :artists, :name, :uri, :previewUrl)");
    query.bindValue(":id", m->id);
    query.bindValue(":idPlaylist", m->idPlaylist);
    query.bindValue(":albumName", m->albumName);
    QString str = "";
    for(int i=0; i<m->artistVector.size(); i++){
        str+=m->artistVector[i];
        if(i != m->artistVector.size()-1)
            str+=";";
    }
    query.bindValue(":artists", str);
    query.bindValue(":name", m->name);
    query.bindValue(":uri", m->uri);
    query.bindValue(":previewUrl", m->previewUrl);
    bool ok = query.exec();
    if(!ok)
    {
        QString lastQuery = query.lastQuery();
        QString lastError = query.lastError().text();
        qDebug(lastQuery.toUtf8());
        qDebug(lastError.toUtf8());
    }
    //m->id = query.lastInsertId().toInt();
}

shared_ptr<model::Music> infra::MusicRepository::getMusic(QString id)
{
    QSqlQuery query(database);
    query.prepare("SELECT * FROM musics WHERE id = :id");
    query.bindValue(":id", id);
    bool ok = query.exec();
    if(!ok)
    {
        QString lastQuery = query.lastQuery();
        QString lastError = query.lastError().text();
        qDebug(lastQuery.toUtf8());
        qDebug(lastError.toUtf8());
        throw SqlException();
    }
    auto m = make_shared<model::Music>();
    while (query.next()) {
        m->albumName = query.value("albumName").toString();
        QStringList parts = query.value("artists").toString().split(QRegExp("(\\;)"));
        QVector<QString> vec;
        for(int i=0; i<parts.size(); i++)
            vec.push_back(parts[i]);
        m->artistVector = vec;
        m->id = query.value("id").toString();
        m->idPlaylist = query.value("idPlaylist").toInt();
        m->name = query.value("name").toString();
        m->previewUrl = query.value("previewUrl").toString();
        m->uri = query.value("uri").toString();
    }
    return m;
}

unique_ptr<vector<shared_ptr<model::Music>>> infra::MusicRepository::getMusic(shared_ptr<model::Playlist> p)const
{
    QSqlQuery query(database);
    query.prepare("SELECT * FROM musics WHERE idPlaylist = :idPlaylist");
    query.bindValue(":idPlaylist", p->id);

    query.exec();
    auto lst = make_unique<vector<shared_ptr<model::Music>>>();
    while (query.next()) {
        auto m = make_shared<model::Music>();
        m->albumName = query.value("albumName").toString();
        QStringList parts = query.value("artists").toString().split(QRegExp("(\\;)"));
        QVector<QString> vec;
        for(int i=0; i<parts.size(); i++)
            vec.push_back(parts[i]);
        m->artistVector = vec;
        m->id = query.value("id").toString();
        m->idPlaylist = query.value("idPlaylist").toInt();
        m->name = query.value("name").toString();
        m->previewUrl = query.value("previewUrl").toString();
        m->uri = query.value("uri").toString();
        lst->push_back(m);
    }
    return lst;
}
