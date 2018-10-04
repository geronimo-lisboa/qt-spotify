#include <gmock/gmock.h>
#include <2-model/UserService.h>
#include <2-model/entities/User.h>
#include <memory>

using namespace std;

TEST(UserServiceTest, CanCreateUser)
{
    model::UserService userService;
    const int sz0 = userService.getUsers()->size();
    std::shared_ptr<model::User> user = std::make_shared<model::User>("code","foobar");
    userService.addUser(user);
    EXPECT_TRUE(user->getId()!=model::User::INVALID_ID);//testa se o id da entidade tá atualizado
    EXPECT_TRUE((sz0+1) == userService.getUsers()->size());//a parada realmente está na tabela?
    std::shared_ptr<model::User> user2 = userService.getUser(user->getId());
    EXPECT_TRUE((*user2)==(*user));//O usuário que foi inserido é o que foi recuperado?
}
int main(int argc, char** argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
