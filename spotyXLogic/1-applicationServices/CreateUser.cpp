#include "CreateUser.h"
#include <2-model/UserService.h>
#include <2-model/AuthenticationService.h>
#include <2-model/entities/User.h>

applicationServices::CreateUser::CreateUser(QObject *parent):
    QObject (parent),
    userService(new model::UserService())
{
    authService = std::make_unique<model::AuthenticationService>(this);
    //    autenticacação bem sucedida
    connect(authService.get(), &model::AuthenticationService::authenticationSuccessful,
            this, &CreateUser::successfulAuthentication);
    //    autenticacação fracassada
    connect(authService.get(), &model::AuthenticationService::authenticationFailed,
            this, &CreateUser::failerAuthentication);

}

void applicationServices::CreateUser::beginCreation()
{
    authService->beginAuthentication();
}

void applicationServices::CreateUser::successfulAuthentication(infra::AuthenticationDTO authDto)
{
    //hora de pegar os dados do cara no spotify
    std::shared_ptr<model::User> newUsu = userService->createFromSpotifyData(authDto.accessToken);
    //ligar o authDTO ao meu usuário
    std::shared_ptr<model::UserSpotifyData> sd = make_shared<model::UserSpotifyData>(authDto);
    userService->updateUserSpotifyData(newUsu, sd);
    qDebug("ok?");
    emit newUserCreated(newUsu);
}

void applicationServices::CreateUser::failerAuthentication()
{
    emit userRefused();
}
