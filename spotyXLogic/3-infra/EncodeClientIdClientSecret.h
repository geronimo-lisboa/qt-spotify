#ifndef EncodeClientSecret_h
#define EncodeClientSecret_h
class QByteArray;
class QString;
namespace infra {
    class EncodeClientIdClientSecret{
    public:
        QByteArray encode(QString clientId, QString clientSecret);
    };
}
#endif
