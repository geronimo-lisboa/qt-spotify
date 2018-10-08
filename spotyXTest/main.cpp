#include <gmock/gmock.h>
#include <2-model/UserService.h>
#include <2-model/entities/User.h>
#include <2-model/entities/UserSpotifyData.h>
#include <3-infra/repository/DatabaseManager.h>
#include <3-infra/repository/UserSpotifyDataRepository.h>
#include <memory>
#include <vector>
#include <3-infra/PostContentBuilder.h>
#include <QByteArray>
#include <3-infra/EncodeClientIdClientSecret.h>
#include <QTextCodec>
#include <1-applicationServices/ListUsers.h>
#include <3-infra/repository/MusicRepository.h>
#include <2-model/entities/Music.h>
#include <2-model/entities/Playlist.h>
#include <QtMultimedia/QMediaPlayer>
#include <QThread>
#include <3-infra/tokenRefresh/TokenRefresh.h>
using namespace std;
//A tabela de musica tá ok? Escrever sql na mão é fonte de erro...
TEST(MusicTest, AddingMusicToDb)
{
    infra::DatabaseManager::instance().purgeDatabase();
    shared_ptr<model::Music> aMusic = make_shared<model::Music>();
    aMusic->albumName="foo";
    QVector<QString> vec;
    vec.push_back("Able");
    vec.push_back("Baker");
    aMusic->artistVector = vec;
    aMusic->id = "bar";
    aMusic->idPlaylist=66;
    aMusic->name="woo";
    aMusic->previewUrl="http://localhost";
    aMusic->uri="sjdfkjafa";

    shared_ptr<model::Playlist> dummyPlaylist = make_shared<model::Playlist>(66, 1, "foobar");

    infra::DatabaseManager::instance().getMusicRepository()->addMusic(aMusic);
    auto musics = infra::DatabaseManager::instance().getMusicRepository()->getMusic(dummyPlaylist);

    EXPECT_TRUE(musics->size() == 1);

    EXPECT_TRUE((*musics)[0]->albumName == aMusic->albumName);
    EXPECT_TRUE((*musics)[0]->id == aMusic->id);
    EXPECT_TRUE((*musics)[0]->idPlaylist == aMusic->idPlaylist);
    EXPECT_TRUE((*musics)[0]->name == aMusic->name);
    EXPECT_TRUE((*musics)[0]->previewUrl == aMusic->previewUrl);
    EXPECT_TRUE((*musics)[0]->uri == aMusic->uri);
    EXPECT_TRUE((*musics)[0]->artistVector.size()==2);
}
//A url obtida do spotify toca? (vai bloquear o teste por 30 s)
TEST(MusicTest, CanIPlayTheMusic){
    infra::DatabaseManager::instance().purgeDatabase();
    shared_ptr<model::Music> aMusic = make_shared<model::Music>();

    aMusic->albumName="Dangerous Days";
    QVector<QString> vec;
    vec.push_back("Perturbator");
    vec.push_back("Dead Astronauts");
    aMusic->artistVector = vec;
    aMusic->id = "5CPWaIaUXld4c3k94i3kIy";
    aMusic->idPlaylist=66;
    aMusic->name="Minuit (feat. Dead Astronauts)";
    aMusic->previewUrl="https://p.scdn.co/mp3-preview/904622d8e959c52f852a26975cdb4bdf35ee525d?cid=568f5c57cd48447eb8c59fafde9f1d34";
    aMusic->uri="spotify:track:5CPWaIaUXld4c3k94i3kIy";

    infra::DatabaseManager::instance().getMusicRepository()->addMusic(aMusic);
    auto storedMusic = infra::DatabaseManager::instance().getMusicRepository()->getMusic("5CPWaIaUXld4c3k94i3kIy");
    QMediaPlayer player;
    player.setMedia(QUrl(storedMusic->previewUrl));
    player.setVolume(100);
    player.play();
    EXPECT_TRUE(aMusic->previewUrl!=nullptr && aMusic->previewUrl.length()>0);
    qDebug("playing aMusic->previewUrl");
    QThread::sleep(31);
}

TEST(UserTest, CanIGetTheTokens)
{
    //O código usa event loop lá embaixo e event loop só funciona em QApplication - não sei como lidar com isso
    //no gtest
//    infra::DatabaseManager::instance().purgeDatabase();
//    shared_ptr<model::UserSpotifyData> userData = make_shared<model::UserSpotifyData>();
//    userData->accessToken = "BQCW6w2xCfLK_xdrHc2GXh9AlTR6Po1H57FmLfZvX5wdE7PYwfoMCVxaNNqGo3S7FOP4ObSPy2X-X8vuhkK8-_4ifr-m4MBAIyY-5niIRYrU8_5Q4774fY2nkDPgTQCX4W-ZZC3LY24WKIsLH2oK7KFYqMIYn-g";
//    userData->code = "AQCe061OyP6SR1GoV7M7Gwa1-yBkEK-_KLG1bouoD9FEvf6P06mXBFvtbtTbmRGyBzeys6KwIqG3RZvpwokuLCE9eJ620SKs8sZ33TQUti2N1Ij9DrArXJDUsuiv_kCUl1B1xmqRFxDIevkzGmhDfgMbyYbtkqzhvCYrE2UoE1pML58l2PNXx20-M3H4JE_pR2HsSBEPHHrfFJrqymjzxzY";
//    userData->refreshToken = "AQDxzLOKu9uAzqbbkOW5tadBMldfe--_05EgUFKM5e_ll6JZh1Z6QNmM-NFace3dpr45KsHFVJak6DwOA-DeR34pWOooMngrY7Tq_lTigKMef1PUEUJ6wzwFXj81BrI5aCRTdg";
//    userData->scope = "user-read-private";

//    shared_ptr<model::User> user = make_shared<model::User>(userData->code, "Able");
//    infra::DatabaseManager::instance().getUserRepository()->addUser(user);
//    EXPECT_TRUE(user->getId() >= 0); //se gravou tá com id novo

//    user->setSpotifyData(userData);
//    userData->idUser = user->getId();
//    infra::DatabaseManager::instance().getUserSpotifyDataRepository()->addSpotifyData(userData);
//    EXPECT_TRUE(userData->id >= 0); //se gravou tá com id novo

//    infra::TokenRefresh refresher;
//    infra::AuthenticationDTO dto = refresher.refresh(*user);
//    EXPECT_TRUE(dto.accessToken != userData->accessToken);
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
    infra::DatabaseManager::instance().purgeDatabase();
    shared_ptr<model::UserSpotifyData> userData = make_shared<model::UserSpotifyData>();
    userData->accessToken = "BQCW6w2xCfLK_xdrHc2GXh9AlTR6Po1H57FmLfZvX5wdE7PYwfoMCVxaNNqGo3S7FOP4ObSPy2X-X8vuhkK8-_4ifr-m4MBAIyY-5niIRYrU8_5Q4774fY2nkDPgTQCX4W-ZZC3LY24WKIsLH2oK7KFYqMIYn-g";
    userData->code = "AQCe061OyP6SR1GoV7M7Gwa1-yBkEK-_KLG1bouoD9FEvf6P06mXBFvtbtTbmRGyBzeys6KwIqG3RZvpwokuLCE9eJ620SKs8sZ33TQUti2N1Ij9DrArXJDUsuiv_kCUl1B1xmqRFxDIevkzGmhDfgMbyYbtkqzhvCYrE2UoE1pML58l2PNXx20-M3H4JE_pR2HsSBEPHHrfFJrqymjzxzY";
    userData->refreshToken = "AQDxzLOKu9uAzqbbkOW5tadBMldfe--_05EgUFKM5e_ll6JZh1Z6QNmM-NFace3dpr45KsHFVJak6DwOA-DeR34pWOooMngrY7Tq_lTigKMef1PUEUJ6wzwFXj81BrI5aCRTdg";
    userData->scope = "user-read-private";

    shared_ptr<model::User> user = make_shared<model::User>(userData->code, "Able");
    infra::DatabaseManager::instance().getUserRepository()->addUser(user);
    EXPECT_TRUE(user->getId() >= 0); //se gravou tá com id novo

    user->setSpotifyData(userData);
    userData->idUser = user->getId();
    infra::DatabaseManager::instance().getUserSpotifyDataRepository()->addSpotifyData(userData);
    EXPECT_TRUE(userData->id >= 0); //se gravou tá com id novo

    userData->refreshToken="foobar";
    infra::DatabaseManager::instance().getUserSpotifyDataRepository()->updateSpotifyData(userData);
    auto data = infra::DatabaseManager::instance().getUserSpotifyDataRepository()->getSpotifyData(userData->id);
    EXPECT_TRUE(data->refreshToken == "foobar");

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
