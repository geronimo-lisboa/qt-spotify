#ifndef User_h
#define User_h
#include <QString>
namespace model
{
////É o meu usuário
    class User
    {
    private:
         int id;
        QString code;
        QString name;
    public:
        const static int INVALID_ID = -1;
        User(QString code, QString name, int id);
        User(QString code, QString name);
        QString getCode();
        void setCode(QString code);
        QString getName();
        void setName(QString name);
        int getId();
        void setId(int id);
        bool operator==(const User& b);
    };
}
#endif
