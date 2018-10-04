#include "UserSpotifyDataRepository.h"
#include "2-model/entities/User.h"
#include "2-model/entities/UserSpotifyData.h"
#include "exceptions/SqlException.h"
#include <QSqlDatabase>
#include<QSqlQuery>
#include<QVariant>
#include<QStringList>
#include<QSqlError>
#include <QDebug>

infra::UserSpotifyDataRepository::UserSpotifyDataRepository(QSqlDatabase &db):
    database(db)
{

}

void infra::UserSpotifyDataRepository::init() const
{
    if(!database.tables().contains("userSpotifyData"))
    {
        QSqlQuery query(database);
        bool ok = query.exec("CREATE TABLE userSpotifyData "
                        "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "idUser INTEGER, "
                        "code TEXT, "
                        "accessToken TEXT, "
                        "tokenType TEXT, "
                        "scope TEXT, "
                        "expiresIn INTEGER, "
                        "refreshToken TEXT )"
        );
        if(!ok)
        {
            throw SqlException();
        }
    }
}

void infra::UserSpotifyDataRepository::addSpotifyData(std::shared_ptr<model::UserSpotifyData> d) const
{
    QSqlQuery query(database);
    query.prepare("INSERT INTO userSpotifyData "
                  "(idUser, code, accessToken, tokenType, scope, expiresIn, refreshToken) "
                  "VALUES "
                  "(:idUser, :code, :accessToken, :tokenType, :scope, :expiresIn, :refreshToken)");
    query.bindValue(":idUser", d->idUser);
    query.bindValue(":code",d->code);
    query.bindValue(":accessToken",d->accessToken);
    query.bindValue(":tokenType",d->tokenType);
    query.bindValue(":scope",d->scope);
    query.bindValue(":expiresIn",d->expiresIn);
    query.bindValue(":refreshToken",d->refreshToken);
    bool ok = query.exec();

    d->id = query.lastInsertId().toInt();

}

void infra::UserSpotifyDataRepository::updateSpotifyData(std::shared_ptr<model::UserSpotifyData> d) const
{
    QSqlQuery query(database);
    query.prepare("UPDATE userSpotifyData "
                  "SET "
                  "code, accessToken, tokenType, "
                  "scope, expiresIn, refreshToken "
                  "VALUES "
                  " :code, :accessToken, :tokenType, "
                  ":scope, :expiresIn, :refreshToken");
    query.bindValue(":code",d->code);
    query.bindValue(":accessToken",d->accessToken);
    query.bindValue(":code",d->code);
    query.bindValue(":tokenType",d->tokenType);
    query.bindValue(":scope",d->scope);
    query.bindValue(":expiresIn",d->expiresIn);
    query.bindValue(":refreshToken",d->refreshToken);
    query.exec();
}

shared_ptr<model::UserSpotifyData> infra::UserSpotifyDataRepository::getSpotifyData(model::User &usu)
{
    QSqlQuery query(database);
    query.prepare("SELECT * FROM userSpotifyData WHERE idUser=:idUser");
    query.bindValue(":idUser",usu.getId());
    query.exec();
    shared_ptr<model::UserSpotifyData>  d ;
    while(query.next()){
        d = make_shared<model::UserSpotifyData>();
        d->id = query.value("id").toInt();
        d->idUser = query.value("idUser").toInt();
        d->code = query.value("code").toString();
        d->accessToken = query.value("accessToken").toString();
        d->tokenType = query.value("tokenType").toString();
        d->scope = query.value("scope").toString();
        d->expiresIn = query.value("expiresIn").toInt();
        d->refreshToken = query.value("refreshToken").toString();
    }
    return d;
}

void infra::UserSpotifyDataRepository::purgeSpotifyData() const
{
    QSqlQuery query(database);
    query.exec("DELETE FROM userSpotifyData");
}
