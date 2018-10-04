#include "UserService.h"
#include "2-model/entities/User.h"
#include <exceptions/TwoRecordsWithSameIdException.h>
using namespace std;

model::UserService::UserService():
    dbManager(infra::DatabaseManager::instance()),
    userRepository(dbManager.getUserRepository()),
    userSpotifyRepository(dbManager.getUserSpotifyDataRepository())
{
}

void model::UserService::addUser(shared_ptr<model::User> usu)
{
    userRepository->addUser(usu);
}

void model::UserService::updateUserSpotifyData(shared_ptr<model::User> usu, shared_ptr<model::UserSpotifyData> data)
{
    if(usu->getSpotifyData()==nullptr){
        data->idUser = usu->getId();
        usu->setSpotifyData(data);
        userSpotifyRepository->addSpotifyData(data);
    }
    else{
        usu->getSpotifyData()->accessToken = data->accessToken;
        usu->getSpotifyData()->code = data->code;
        usu->getSpotifyData()->expiresIn = data->expiresIn;
        usu->getSpotifyData()->refreshToken = data->refreshToken;
        usu->getSpotifyData()->scope = data->scope;
        usu->getSpotifyData()->tokenType = data->tokenType;
        userSpotifyRepository->updateSpotifyData(usu->getSpotifyData());
    }
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

unique_ptr<vector<shared_ptr<model::User> > > model::UserService::getUser(QString name)
{
    return userRepository->getUsers(name);
}

unique_ptr<vector<shared_ptr<model::User>>> model::UserService::getUsers()
{
    return userRepository->getUsers();
}

void model::UserService::refreshToken(shared_ptr<model::User> user)
{
    //vai no spotify e pede os tokens novos
}
