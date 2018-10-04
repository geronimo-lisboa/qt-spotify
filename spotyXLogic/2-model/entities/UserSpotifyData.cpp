#include "UserSpotifyData.h"

bool model::UserSpotifyData::operator==(const model::UserSpotifyData &b)
{
    return this->id==b.id;
}

model::UserSpotifyData::UserSpotifyData(infra::AuthenticationDTO dto, int idUser, int id)
{
    this->accessToken=dto.accessToken;
    this->code=dto.code;
    this->expiresIn=dto.expiresIn;
    this->id=id;
    this->idUser = idUser;
    this->refreshToken=dto.refreshToken;
    this->scope=dto.scope;
}

model::UserSpotifyData::UserSpotifyData()
{
    this->id=-1;
}

model::UserSpotifyData::UserSpotifyData(infra::AuthenticationDTO dto)
{
    this->accessToken=dto.accessToken;
    this->code=dto.code;
    this->expiresIn=dto.expiresIn;
    this->id=-1;
    this->idUser = -10;
    this->refreshToken=dto.refreshToken;
    this->scope=dto.scope;
    this->tokenType=dto.tokenType;
}
