#ifndef UserService_h
#define UserService_h
#include<memory>
#include <vector>
#include "3-infra/repository/DatabaseManager.h"
#include "3-infra/repository/UserRepository.h"
using namespace std;

namespace infra {
    class TokenRefresh;
}

namespace model
{
    class User;
    class UserService
    {
    private:
        infra::DatabaseManager& dbManager;
        shared_ptr<infra::UserRepository> userRepository;
        shared_ptr<infra::UserSpotifyDataRepository> userSpotifyRepository;
        shared_ptr<infra::TokenRefresh> tokenRefresher;
    public:
        UserService();
        shared_ptr<User> createFromSpotifyData(QString code);
        void addUser(shared_ptr<User> usu);
        void updateUserSpotifyData(shared_ptr<User> usu, shared_ptr<UserSpotifyData> data);
        shared_ptr<User> getUser(int id);
        unique_ptr<vector<shared_ptr<model::User>>> getUser(QString name);
        unique_ptr<vector<shared_ptr<model::User>>> getUsers();
        void refreshToken(shared_ptr<User> user);
    };
}
#endif
