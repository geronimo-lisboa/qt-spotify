#include "ListUsers.h"
#include "2-model/UserService.h"
#include "2-model/entities/User.h"

applicationServices::ListUsers::ListUsers()
{
    userService = make_unique<model::UserService>();
}

unique_ptr<vector<shared_ptr<model::User> > > applicationServices::ListUsers::getUserList()
{
    return userService->getUsers();
}
