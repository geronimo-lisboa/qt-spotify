#ifndef AuthenticationPage_h
#define AuthenticationPage_h
#include <QtCore>
#include <QWebEngineView>
namespace infra
{
    class AuthenticationPage : public QObject
    {
        Q_OBJECT
    private:
        QString stateString;
        QString clientId;
        QWebEngineView* view;
    public:
        AuthenticationPage(QString clientId, QString stateString, QObject* parent = nullptr);
        void show();
        ~AuthenticationPage();
    public slots:
        void close();
    };
}
#endif
