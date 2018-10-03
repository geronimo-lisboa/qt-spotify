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
        void init();
        void addUser(std::shared_ptr<model::User> usu);
        void updateUser(std::shared_ptr<model::User> usu);
        unique_ptr<ListOfUsers> getUsers();
    };
}
#endif
