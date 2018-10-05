#ifndef ListUsers_h
#define ListUsers_h
#include <memory>
#include <vector>
using namespace std;
namespace model {
    class User;
    class UserService;
}

namespace applicationServices{
    ////Serve p/ fazer o caso de uso de listar usuários.
    class ListUsers{
    private:
        unique_ptr<model::UserService> userService;
    public:
        ListUsers();
        unique_ptr<vector<shared_ptr<model::User>>> getUserList();
    };
}
#endif
