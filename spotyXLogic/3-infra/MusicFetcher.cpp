#include "MusicFetcher.h"
#include "PostContentBuilder.h"
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>
#include <qnetworkrequest.h>
#include <QNetworkReply>
#include <2-model/entities/User.h>
#include <2-model/entities/UserSpotifyData.h>
#include <QDebug>
#include <3-infra/tokenRefresh/TokenRefresh.h>
#include <2-model/entities/Music.h>
#include <3-infra/repository/DatabaseManager.h>
#include <vector>
using namespace std;

infra::MusicFetcher::MusicFetcher(QObject *parent):
    QObject (parent)
{

}

unique_ptr<vector<shared_ptr<model::Music>>> infra::MusicFetcher::search(QString query, shared_ptr<model::User>user)
{
   QUrl url("https://api.spotify.com/v1/search");
   QUrlQuery urlQuery;
   urlQuery.addQueryItem("q",query.toUtf8().toPercentEncoding());
   urlQuery.addQueryItem("type", "track");
   urlQuery.addQueryItem("limit", "20");
   url.setQuery(urlQuery);
   QNetworkRequest request(url);

   QString _authK="Authorization";
   QString _accessK = user->getSpotifyData()->accessToken.toUtf8();
   QString _accessV = "Bearer "+ user->getSpotifyData()->accessToken;

   request.setRawHeader(_authK.toUtf8(), _accessV.toUtf8());

   QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
   QNetworkReply* reply = networkManager->get(request);
   QEventLoop loop;
   loop.connect(networkManager, SIGNAL(finished(QNetworkReply*)), SLOT(quit()));
   loop.exec();
   QByteArray data = reply->readAll();//os dados tão aqui
   //testa por erros
   QJsonObject rootObject = QJsonDocument::fromJson(data).object();

    auto errorData = rootObject.value("error");
    //TEM ERRO
    if(errorData!=QJsonValue::Undefined){
        auto errorStatus = errorData.toObject().value("status");
//        if(errorStatus.toInt()==401){
            qDebug("token velho, preciso dar refresh e tentar de novo");
            //refresh no token
            shared_ptr<infra::TokenRefresh> tokenRefresher = make_shared<infra::TokenRefresh>(this);
            auto dto = tokenRefresher->refresh(*user);
            std::shared_ptr<model::UserSpotifyData> usData = make_shared<model::UserSpotifyData>
                    (dto, user->getSpotifyData()->id,user->getSpotifyData()->id);
            //agora guarda o token novo
            user->setSpotifyData(usData);
            DatabaseManager::instance().getUserSpotifyDataRepository()->updateSpotifyData(usData);
            //tenta essa função de novo
            return this->search(query, user);
//        }
//        qDebug("ERRO AQUI. PQ?")
    }
    else{//token tá de boa
        qDebug(data);
        auto queryResult = rootObject.value("tracks").toObject();
        auto items = queryResult.value("items").toArray();//a lista retornada.
        unique_ptr<vector<shared_ptr<model::Music>>> listOfMusics(new vector<shared_ptr<model::Music>>());
        for(auto i = items.begin(); i!=items.end(); ++i)
        {
            auto currentItem = (*i).toObject();
            //Pega o nome do album
            auto trackAlbum = currentItem.value("album").toObject();
            QString albumName = trackAlbum.value("name").toString();
            //pega os artistas
            QVector<QString> artistVector;
            auto artistsList = currentItem.value("artists").toArray();
            for(auto a = artistsList.begin(); a!=artistsList.end(); ++a)
            {
                auto currentArtist = (*a).toObject();
                QString artistName = currentArtist.value("name").toString();
                artistVector.push_back(artistName);
            }//com isso eu tenho a lista de artistas.
            QString id = currentItem.value("id").toString();
            QString name = currentItem.value("name").toString();
            QString uri = currentItem.value("uri").toString();

            shared_ptr<model::Music> music = make_shared<model::Music>();
            music->id = id;
            music->albumName = albumName;
            music->artistVector = artistVector;
            music->name = name;
            music->uri = uri;
            music->previewUrl = currentItem.value("preview_url").toString();
            if (music->previewUrl!=nullptr && music->previewUrl.size()>0)
                listOfMusics->push_back(music);
        }
        return listOfMusics;
    }
}
