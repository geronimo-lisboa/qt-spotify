#ifndef UserRepository_h
#define UserRepository_h
#include <vector>
#include <memory>
//forward declarations
class QSqlDatabase;
namespace model
{
    class User;
}
using namespace std;
namespace infra
{
    class UserRepository
    {
    private:
        QSqlDatabase& database;
    public:
        typedef vector<shared_ptr<model::User>> ListOfUsers;
        UserRepository(QSqlDatabase& db);
        //Todos os métodos dessa classe são stateless
        void init() const;
        void addUser(std::shared_ptr<model::User> usu) const;
        void updateUser(std::shared_ptr<model::User> usu) const;
        unique_ptr<ListOfUsers> getUsers()const;
        unique_ptr<ListOfUsers> getUsers(const int id)const;
        void purgeUsers()const;
    };
}
#endif
