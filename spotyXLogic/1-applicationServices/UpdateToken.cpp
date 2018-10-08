#include "UpdateToken.h"
#include "2-model/entities/User.h"
#include "2-model/UserService.h"

applicationServices::UpdateToken::UpdateToken(QObject *obj, shared_ptr<model::User> user):
    user(user),
    userService(new model::UserService())
{

}

void applicationServices::UpdateToken::Refresh()
{
    userService->refreshToken(user);
}
