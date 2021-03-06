#-------------------------------------------------
#
# Project created by QtCreator 2018-10-03T13:16:59
#
#-------------------------------------------------

QT       += network sql webenginewidgets

QT       -= gui

TARGET = spotyXLogic
TEMPLATE = lib
CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        spotyxlogic.cpp \
    2-model/AuthenticationService.cpp \
    3-infra/AuthenticationPage.cpp \
    3-infra/AuthenticationServer.cpp \
    2-model/entities/User.cpp \
    3-infra/repository/UserRepository.cpp \
    3-infra/repository/DatabaseManager.cpp \
    2-model/UserService.cpp \
    2-model/entities/UserSpotifyData.cpp \
    3-infra/repository/UserSpotifyDataRepository.cpp \
    3-infra/tokenRefresh/TokenRefresh.cpp \
    3-infra/PostContentBuilder.cpp \
    3-infra/EncodeClientIdClientSecret.cpp \
    1-applicationServices/ListUsers.cpp \
    1-applicationServices/CreateUser.cpp \
    3-infra/UserDataFetcher.cpp \
    1-applicationServices/SearchMusic.cpp \
    2-model/MusicService.cpp \
    3-infra/MusicFetcher.cpp \
    2-model/entities/Music.cpp \
    1-applicationServices/ManagePlaylist.cpp \
    2-model/entities/Playlist.cpp \
    2-model/PlaylistService.cpp \
    3-infra/repository/PlaylistRepository.cpp \
    3-infra/repository/MusicRepository.cpp \
    1-applicationServices/UpdateToken.cpp


HEADERS += \
        spotyxlogic.h \
    2-model/AuthenticationService.h \
    3-infra/AuthenticationPage.h \
    3-infra/AuthenticationServer.h \
    exceptions/IniFileNotPresentException.h \
    exceptions/exceptionBox.h \
    2-model/entities/User.h \
    3-infra/repository/UserRepository.h \
    3-infra/repository/DatabaseManager.h \
    2-model/UserService.h \
    exceptions/TwoRecordsWithSameIdException.h \
    exceptions/SqlException.h \
    3-infra/authenticaton/AuthenticationDTO.h \
    2-model/entities/UserSpotifyData.h \
    3-infra/repository/UserSpotifyDataRepository.h \
    3-infra/tokenRefresh/TokenRefresh.h \
    3-infra/PostContentBuilder.h \
    3-infra/EncodeClientIdClientSecret.h \
    1-applicationServices/ListUsers.h \
    1-applicationServices/CreateUser.h \
    3-infra/UserDataFetcher.h \
    1-applicationServices/SearchMusic.h \
    2-model/MusicService.h \
    3-infra/MusicFetcher.h \
    2-model/entities/Music.h \
    1-applicationServices/ManagePlaylist.h \
    2-model/entities/Playlist.h \
    2-model/PlaylistService.h \
    3-infra/repository/PlaylistRepository.h \
    3-infra/repository/MusicRepository.h \
    1-applicationServices/UpdateToken.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}


#inclui o QtWebApp e o arquivo de confuguracao
QT += network
include(QtWebApp/QtWebApp/httpserver/httpserver.pri)

DEFINES += INI_FILE_PATH=\\\"D:/programacao/estudos-qt/projetoProva/spotyX/spotify-authentication-test.ini\\\"
