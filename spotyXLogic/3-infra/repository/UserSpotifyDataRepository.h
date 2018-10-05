#ifndef UserSpotifyDataRepository_h
#define UserSpotifyDataRepository_h
#include <vector>
#include <memory>
//forward declarations
class QSqlDatabase;
namespace model
{
    class UserSpotifyData;
    class User;
}
using namespace std;
namespace infra
{
    class UserSpotifyDataRepository
    {
    private:
        QSqlDatabase& database;
    public:
        typedef vector<shared_ptr<model::UserSpotifyData>> ListOfSpotifyData;
        UserSpotifyDataRepository(QSqlDatabase& db);
        //Todos os métodos dessa classe são stateless
        void init() const;
        void addSpotifyData(std::shared_ptr<model::UserSpotifyData> d) const;
        void updateSpotifyData(std::shared_ptr<model::UserSpotifyData> d) const;
        shared_ptr<model::UserSpotifyData> getSpotifyData(model::User& usu);
        shared_ptr<model::UserSpotifyData> getSpotifyData(int id);
        void purgeSpotifyData()const;
    };
}
#endif
