#include <1-applicationServices/SearchMusic.h>
#include "UserWindow.h"
#include "ui_UserWindow.h"
#include <2-model/entities/Playlist.h>
#include <2-model/entities/Music.h>
#include <2-model/entities/User.h>
#include <QInputDialog>
#include <QObjectList>
#include <memory>
#include <QtMultimedia/QMediaPlayer>
#include <1-applicationServices/ManagePlaylist.h>
#include <1-applicationServices/UpdateToken.h>
#include <QMessageBox>
#include <QTimer>
using namespace  std;

void UserWindow::makeSureThereIsLayout(QWidget* wid)
{
    if(wid->layout()==nullptr){
        wid->setLayout(new QVBoxLayout(this));
    }
}

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
    //pra garantir q tem layout
    makeSureThereIsLayout(ui->scrollAreaWidgetContents);
    makeSureThereIsLayout(ui->scrollAreaWidgetContents_2);
    makeSureThereIsLayout(ui->scrollAreaWidgetContents_3);

    player = new QMediaPlayer(this);
    assemblePlaylistSet();

    this->selectedPlaylist = managePlaylist->chooseInitialPlaylist(user);
    updateSelectedPlaylistTracklist(this->selectedPlaylist);
    //Dá refresh no token e agenda refresh regular
    applicationServices::UpdateToken* tokenUpdater = new applicationServices::UpdateToken(this, user);
    tokenUpdater->Refresh();
    refreshTimer = new QTimer(this);
    refreshTimer->setInterval(100000);
    refreshTimer->setSingleShot(false);
    connect(refreshTimer, &QTimer::timeout, tokenUpdater, &applicationServices::UpdateToken::Refresh);
}

UserWindow::~UserWindow()
{
    delete ui;
    QCoreApplication::quit();
}

void UserWindow::btnTesteBuscaMusicaClick()
{
    clearPointerList(listOfSearchResults);

    QString searchParams = ui->edtBusca->text();
    unique_ptr<vector<shared_ptr<model::Music>>> listOfMusic = searchMusicService->searchMusic(searchParams, user);
    if(listOfMusic->size()==0)
    {
        QMessageBox msgBox;
        msgBox.setText("Nenhuma musica encontrada.");
        msgBox.exec();
    }
    else
    {
        QWidget* wid = ui->scrollAreaWidgetContents;
        for_each(listOfMusic->begin(), listOfMusic->end(),[wid, this](shared_ptr<model::Music> currentMusic){
            QWidget* rec = assembleSearchResultRecord(currentMusic);
            listOfSearchResults.push_back(rec);
            wid->layout()->addWidget(rec);
        });
    }
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
        assemblePlaylistSet();
        updateSelectedPlaylistTracklist(selectedPlaylist);
    }

}

QWidget* UserWindow::assembleMusicRecord(std::shared_ptr<model::Music> m)
{
    QFrame* frame = new QFrame(this);
    QHBoxLayout* layout = new QHBoxLayout(frame);
    frame->setLayout(layout);
    //nome
    QLabel* lbNome = new QLabel(frame);
    lbNome->setText(m->name);
    layout->addWidget(lbNome);
    //artista
    QLabel* lbArtista = new QLabel(frame);
    lbArtista->setText(m->concatenateArtists());
    layout->addWidget(lbArtista);
    //botão de play
    QPushButton* btnPlay = new QPushButton(frame);
    btnPlay->setText("PLAY");
    layout->addWidget(btnPlay);
    //evento de play
    connect(btnPlay, &QPushButton::pressed,
            this, [player = this->player, m](){
                    player->setMedia(QUrl(m->previewUrl));
                    player->setVolume(50);
                    player->play();
    });
    return frame;
}

void UserWindow::updateSelectedPlaylistTracklist(shared_ptr<model::Playlist> lst)
{
    if(selectedPlaylist == nullptr)
    {
        return;//Só vai acontecer em um usuário completamente novo no sistema, sem playlist alguma.
    }
    this->selectedPlaylist = lst;
    //limpa o campo da playlist
    clearPointerList(listOfMusics);
    QWidget* wid = ui->scrollAreaWidgetContents_3;
    //p/cada musica da lista, cria uma linha na area da musica.
    for_each(selectedPlaylist->musics->begin(),
             selectedPlaylist->musics->end(),
             [this, wid](shared_ptr<model::Music> m){
        //frame
        auto frame = assembleMusicRecord(m);
        wid->layout()->addWidget(frame);
        this->listOfMusics.push_back(frame);
    });
}

QWidget *UserWindow::assembleSearchResultRecord(std::shared_ptr<model::Music> m)
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

    connect(btnAddToPlaylist, &QPushButton::pressed,
            this, [this, m](){
        //se não tem playlist tem que criar uma.
        if(this->selectedPlaylist == nullptr){
            this->btnNewPlaylistClick();
        }
        assert(this->selectedPlaylist!=nullptr);
        this->managePlaylist->addMusicToPlaylist(this->selectedPlaylist, m);
        this->updateSelectedPlaylistTracklist(this->selectedPlaylist);
    });
    return frame;
}

QWidget *UserWindow::assembleUserPlaylistSetRecord(std::shared_ptr<model::Playlist> m)
{
    //nome
    QFrame* frame = new QFrame(this);
    QHBoxLayout* layout = new QHBoxLayout(frame);
    frame->setLayout(layout);
    QPushButton* openListBtn = new QPushButton(frame);
    openListBtn->setText(m->name);
    connect(openListBtn, &QPushButton::pressed, this, [this, m](){
        this->updateSelectedPlaylistTracklist(m);
    });
    layout->addWidget(openListBtn);
    return frame;
}

void UserWindow::clearPointerList(std::vector<QWidget*>& list){
    if(list.size()>0)
    {
        for(int i=0; i<list.size(); i++){
            if(list[i]!=nullptr)
            {
                delete list[i];
                list[i] = nullptr;
            }
        }
        list.clear();
    }
}

void UserWindow::assemblePlaylistSet()
{
    clearPointerList(listOfPlaylists);
    auto playlistSet = this->user->getPlaylist();
    if(playlistSet==nullptr)
    {
        return;
    }
    else
    {
        QWidget* wid = ui->scrollAreaWidgetContents_2;
        for_each(playlistSet->begin(), playlistSet->end(),[wid, this](shared_ptr<model::Playlist> p){
            QWidget* w = assembleUserPlaylistSetRecord(p);
            listOfPlaylists.push_back(w);
            wid->layout()->addWidget(w);
        });
    }
}
