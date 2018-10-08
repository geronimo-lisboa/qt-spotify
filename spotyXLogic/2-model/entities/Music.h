#ifndef Music_H
#define Music_H

#include <QString>
#include <QVector>


namespace model {
    class Music{
    public:
        QString id;
        int idPlaylist;        
        QString albumName;
        QVector<QString> artistVector;
        QString name;
        QString uri;
        QString previewUrl;

        inline QString concatenateArtists()const {
            QString str = "";
            for(int i=0; i<artistVector.size(); i++){
                str+=artistVector[i]+" ";
            }
            return str;
        }
    };
}
#endif
