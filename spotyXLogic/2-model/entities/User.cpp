#include "User.h"

model::User::User(QString code, QString name,  int id)
{
    this->code = code;
    this->name = name;
    this->id = id;
}

QString model::User::getCode()
{
    return code;
}

void model::User::setCode(QString code)
{
    this->code = code;
}

QString model::User::getName()
{
    return this->name;
}

void model::User::setName(QString name)
{
    this->name = name;
}

int model::User::getId()
{
    return this->id;
}

void model::User::setId(int id)
{
    this->id = id;
}
