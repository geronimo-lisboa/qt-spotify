#ifndef USERWINDOW_H
#define USERWINDOW_H
#include <memory>
#include <QWidget>
#include <QMediaPlayer>

using namespace std;
class QTimer;
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
    void updateSelectedPlaylistTracklist(shared_ptr<model::Playlist> lst);
    QTimer* refreshTimer;
    std::vector<QWidget*> listOfPlaylists;
    std::vector<QWidget*> listOfSearchResults;
    std::vector<QWidget*> listOfMusics;
    QMediaPlayer *player ;
    QWidget* assembleSearchResultRecord(std::shared_ptr<model::Music> m);
    QWidget* assembleUserPlaylistSetRecord(std::shared_ptr<model::Playlist> p);
    QWidget* assembleMusicRecord(std::shared_ptr<model::Music> m);
    void assemblePlaylistSet();

    Ui::UserWindow *ui;
    shared_ptr<model::User> user;
    shared_ptr<model::Playlist> selectedPlaylist;
    unique_ptr<applicationServices::SearchMusic> searchMusicService;
    unique_ptr<applicationServices::ManagePlaylist> managePlaylist;
    void makeSureThereIsLayout(QWidget* wid);
    void clearPointerList(std::vector<QWidget*>& list);
};

#endif // USERWINDOW_H
