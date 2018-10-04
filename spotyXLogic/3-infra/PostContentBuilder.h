#ifndef PostContentBuilder_h
#define PostContentBuilder_h
#include <string>
#include <map>
#include <QByteArray>
namespace infra {
    class PostContentBuilder{
    private:
        std::map<std::string, std::string> table;
    public:
        void add(std::string k, std::string v);
        QByteArray getAssembled()const;
    };

}
#endif
