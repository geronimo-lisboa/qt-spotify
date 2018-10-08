#include <gmock/gmock.h>
#include <2-model/UserService.h>
#include <2-model/entities/User.h>
#include <2-model/entities/UserSpotifyData.h>
#include <3-infra/repository/DatabaseManager.h>
#include <3-infra/repository/UserSpotifyDataRepository.h>
#include <memory>
#include <3-infra/PostContentBuilder.h>
#include <QByteArray>
#include <3-infra/EncodeClientIdClientSecret.h>
#include <QTextCodec>
#include <1-applicationServices/ListUsers.h>
#include <3-infra/repository/MusicRepository.h>

using namespace std;
TEST(MusicTest, IsInsertWorking)
{
    auto musicRepo = infra::DatabaseManager::instance().getMusicRepository();
}

TEST(ListUserTest, IsTheListCorrect)
{
    auto userRepo = infra::DatabaseManager::instance().getUserRepository();
    const int sz = userRepo->getUsers()->size();
    applicationServices::ListUsers listUsers;
    const int sz2 = listUsers.getUserList()->size();
    EXPECT_TRUE(sz==sz2);
}

TEST(UtilitiesTest, ClientIdClientSecretEncoding)
{
    infra::EncodeClientIdClientSecret encoder;
    QByteArray encodedData =encoder.encode("568f5c57cd48447eb8c59fafde9f1d34", "43131196b0fa4885aa4ae9338cf4c961");

    QString encodedDataAsString = QTextCodec::codecForUtfText(encodedData)->toUnicode(encodedData);
    QString target="QXV0aG9yaXphdGlvbjogQmFzaWMgNTY4ZjVjNTdjZDQ4NDQ3ZWI4YzU5ZmFmZGU5ZjFkMzQ6NDMxMzExOTZiMGZhNDg4NWFhNGFlOTMzOGNmNGM5NjE=";
    EXPECT_TRUE(encodedDataAsString == target);
}

TEST(UtilitiesTest, IsSpotifyDataUpdating)
{
    auto spotyRepo = infra::DatabaseManager::instance().getUserSpotifyDataRepository();
    shared_ptr<model::User> dummy = std::make_shared<model::User>("x","x", 2);
    auto spotyData0 = spotyRepo->getSpotifyData(*dummy);
    spotyData0->accessToken="is this updated?";
    spotyRepo->updateSpotifyData(spotyData0);
    auto spotyData1 = spotyRepo->getSpotifyData(spotyData0->id);
    EXPECT_TRUE(spotyData1->accessToken=="is this updated?");

}

TEST(UtilitiesTest, IsPostBuilderWorking)
{
    infra::PostContentBuilder builder;
    builder.add("name", "charles bronson");
    builder.add("ocupation", "gunslinger");
    QByteArray arr = builder.getAssembled();
    std::string str = "name=charles%20bronson&ocupation=gunslinger";
    QByteArray expectation = QByteArray::fromStdString(str);
    EXPECT_TRUE(arr.toStdString()==expectation.toStdString());
}

TEST(UserServiceTest, CanCreateUser)
{
    model::UserService userService;
    const int sz0 = userService.getUsers()->size();
    std::shared_ptr<model::User> user = std::make_shared<model::User>("code","foobar");
    userService.addUser(user);
    EXPECT_TRUE(user->getId()!=model::User::INVALID_ID);//testa se o id da entidade tá atualizado
    EXPECT_TRUE((sz0+1) == userService.getUsers()->size());//a parada realmente está na tabela?
    std::shared_ptr<model::User> user2 = userService.getUser(user->getId());
    EXPECT_TRUE((*user2)==(*user));//O usuário que foi inserido é o que foi recuperado?
}

TEST(UserServiceTest, IsSpotDataPersistenceWorking)
{
    //cria um cara
    model::UserService userService;
    std::shared_ptr<model::User> user = std::make_shared<model::User>("code","foobar");
    userService.addUser(user);
    EXPECT_TRUE(user->getId()!=model::User::INVALID_ID);//testa se o id da entidade tá atualizado
    //Cria os dados de spotify
    auto spotyRepo = infra::DatabaseManager::instance().getUserSpotifyDataRepository();
    shared_ptr<model::UserSpotifyData> data = make_shared<model::UserSpotifyData>();
    data->accessToken="ipsum";
    data->code="loren";
    data->expiresIn=666;
    data->refreshToken="dolor";
    data->scope="sit";
    data->tokenType="amet";
    data->idUser = user->getId();
    spotyRepo->addSpotifyData(data);
    EXPECT_TRUE(data->id>-1);
    //Os dados tão lá?
    auto usuData = spotyRepo->getSpotifyData(*user);
    EXPECT_TRUE(usuData!=nullptr);

}

TEST(UserServiceTest, DealWithSpotifyData){
    model::UserService userService;

    //cria um cara
    std::shared_ptr<model::User> user = std::make_shared<model::User>("code","foobar");
    userService.addUser(user);
    EXPECT_TRUE(user->getId()!=model::User::INVALID_ID);//testa se o id da entidade tá atualizado


    shared_ptr<model::UserSpotifyData> data = make_shared<model::UserSpotifyData>();
    data->accessToken="ipsum";
    data->code="loren";
    data->expiresIn=666;
    data->refreshToken="dolor";
    data->scope="sit";
    data->tokenType="amet";
    userService.updateUserSpotifyData(user,data);

    auto spotyRepo = infra::DatabaseManager::instance().getUserSpotifyDataRepository();
    auto savedData = spotyRepo->getSpotifyData(*user);

    EXPECT_TRUE(savedData->id == data->id);
}
int main(int argc, char** argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
