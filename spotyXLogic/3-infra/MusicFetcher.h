#ifndef MusicFetcher_h
#define MusicFetcher_h
#include <QtCore>
#include <memory>
#include <QString>
using namespace std;
namespace model
{
    class User;
    class Music;
}
namespace infra {
    class MusicFetcher : public QObject{
        Q_OBJECT
    public:
        MusicFetcher(QObject* parent=nullptr);
        unique_ptr<vector<shared_ptr<model::Music>>> search(QString query, shared_ptr<model::User>user);
    };
}
#endif
