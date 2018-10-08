#ifndef MusicRepository_h
#define MusicRepository_h
#include <vector>
#include <memory>
using namespace std;
class QSqlDatabase;
namespace model {
    class Playlist;
    class Music;
}

namespace infra{
    class MusicRepository{
    private:
        QSqlDatabase& database;
    public:
        MusicRepository(QSqlDatabase& db);
        void init()const;
        void addMusic(shared_ptr<model::Music> m)const ;
        unique_ptr<vector<shared_ptr<model::Music>>> getMusic(shared_ptr<model::Playlist>p)const;
    };
}
#endif