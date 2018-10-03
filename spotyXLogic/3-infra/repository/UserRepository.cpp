#include "UserRepository.h"
#include "2-model/entities/User.h"
#include <QSqlDatabase>
#include<QSqlQuery>
#include<QVariant>
#include<QStringList>
infra::UserRepository::UserRepository(QSqlDatabase &db):
    database(db)
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
        auto id = query.value("id").toInt();
        auto name = query.value("name").toString();
        auto code = query.value("code").toString();
        unique_ptr<model::User> u = make_unique<model::User>(code, name, id);
        lst->push_back(move(u));
    }
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
        auto id = query.value("id").toInt();
        auto name = query.value("name").toString();
        auto code = query.value("code").toString();
        unique_ptr<model::User> u = make_unique<model::User>(code, name, id);
        lst->push_back(move(u));
    }
    return lst;
}