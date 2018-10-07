#ifndef USERWINDOW_H
#define USERWINDOW_H
#include <memory>
#include <QWidget>
#include <QMediaPlayer>

using namespace std;

namespace Ui {
class UserWindow;
}

namespace model {
    class User;
    class Music;
    class Playlist;
}
namespace applicationServices {
    class SearchMusic;
    class ManagePlaylist;
}

class UserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UserWindow(shared_ptr<model::User> user,
                        QWidget *parent = nullptr);
    ~UserWindow();

public slots:
    void btnTesteBuscaMusicaClick();
    void btnNewPlaylistClick();
private:
    QMediaPlayer *player ;
    QWidget* assembleSearchResult(std::shared_ptr<model::Music> m);
    Ui::UserWindow *ui;
    shared_ptr<model::User> user;
    shared_ptr<model::Playlist> selectedPlaylist;
    unique_ptr<applicationServices::SearchMusic> searchMusicService;
    unique_ptr<applicationServices::ManagePlaylist> managePlaylist;
};

#endif // USERWINDOW_H
