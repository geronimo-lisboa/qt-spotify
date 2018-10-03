#include "UserService.h"
#include "2-model/entities/User.h"
#include <exceptions/TwoRecordsWithSameIdException.h>
using namespace std;

model::UserService::UserService():
    dbManager(infra::DatabaseManager::instance()),
    userRepository(dbManager.getUserRepository())
{
}

void model::UserService::addUser(shared_ptr<model::User> usu)
{
    userRepository->addUser(usu);
}

shared_ptr<model::User> model::UserService::getUser(int id)
{
    auto resultSet = userRepository->getUsers(id);
    if(resultSet->size()==0)
    {
        return nullptr;
    }
    if(resultSet->size()==1)
    {
        return (*resultSet)[0];
    }
    else
    {
        throw TwoRecordsWithSameIdException();
    }
}

unique_ptr<vector<shared_ptr<model::User>>> model::UserService::getUsers()
{
    return userRepository->getUsers();
}
