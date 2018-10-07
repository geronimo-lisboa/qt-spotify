#include <1-applicationServices/SearchMusic.h>
#include "UserWindow.h"
#include "ui_UserWindow.h"
#include <2-model/entities/Music.h>
#include <QInputDialog>
#include <QObjectList>
#include <memory>
#include <QtMultimedia/QMediaPlayer>
#include <1-applicationServices/ManagePlaylist.h>

using namespace  std;
UserWindow::UserWindow(shared_ptr<model::User> user,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserWindow),
    user(user),
    searchMusicService(new applicationServices::SearchMusic()),
    managePlaylist(new applicationServices::ManagePlaylist())
{
    ui->setupUi(this);
    connect(ui->btnTesteBuscaMusica, &QPushButton::pressed,
            this, &UserWindow::btnTesteBuscaMusicaClick);
    connect(ui->btnNewPlaylist, &QPushButton::pressed,
            this, &UserWindow::btnNewPlaylistClick);

    QWidget* wid = ui->scrollAreaWidgetContents;
    if(wid->layout()==nullptr){
        wid->setLayout(new QVBoxLayout(this));
    }
    //auto x = wid->layout();
    player = new QMediaPlayer(this);
}

UserWindow::~UserWindow()
{
    delete ui;
    QCoreApplication::quit();
}

void UserWindow::btnTesteBuscaMusicaClick()
{
    QString searchParams = ui->edtBusca->text();
    unique_ptr<vector<shared_ptr<model::Music>>> listOfMusic = searchMusicService->searchMusic(searchParams, user);
    QWidget* wid = ui->scrollAreaWidgetContents;
    for_each(listOfMusic->begin(), listOfMusic->end(),[wid, this](shared_ptr<model::Music> currentMusic){
        QWidget* rec = assembleSearchResult(currentMusic);
        wid->layout()->addWidget(rec);
    });
}

void UserWindow::btnNewPlaylistClick()
{
    //popup asking name
    bool ok;
    QString text = QInputDialog::getText(this, tr("My program"),
                                         tr("name of the playlist:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    if (ok && !text.isEmpty())
    {
        //create the thing
        selectedPlaylist = managePlaylist->createNew(text, user);
    }
}

QWidget *UserWindow::assembleSearchResult(std::shared_ptr<model::Music> m)
{
    QFrame* frame = new QFrame(this);
    QHBoxLayout* layout = new QHBoxLayout(frame);
    frame->setLayout(layout);
    QLabel* lbNome = new QLabel(frame);
    lbNome->setText(m->name);
    layout->addWidget(lbNome);

    QLabel* lbArtista = new QLabel(frame);
    lbArtista->setText(m->concatenateArtists());
    layout->addWidget(lbArtista);

    QPushButton* btnPlay = new QPushButton(frame);
    btnPlay->setText("PLAY");
    layout->addWidget(btnPlay);

    connect(btnPlay, &QPushButton::pressed,
            this, [player = this->player, m](){
                    player->setMedia(QUrl(m->previewUrl));
                    player->setVolume(50);
                    player->play();
    });

    QPushButton* btnAddToPlaylist = new QPushButton(frame);
    btnAddToPlaylist->setText("Add");
    layout->addWidget(btnAddToPlaylist);

    connect(btnPlay, &QPushButton::pressed,
            this, [player = this->player, m](){
        qDebug("nao implementado ainda");
    });
    return frame;
}
