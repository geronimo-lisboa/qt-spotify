#ifndef UserDataFecther_h
#define UserDataFecther_h
#include <QString>
#include <QObject>
namespace infra {
    class UserDataFetcher:public QObject{
        Q_OBJECT
    public:
        UserDataFetcher(QObject* obj = nullptr);
        QString getName(QString code);
    };
}
#endif
