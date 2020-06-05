#ifndef MUSIC_H
#define MUSIC_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileInfo>

class Music
{
public:
    Music();
    ~Music();
    void playMusic(int volume);
private:
    QMediaPlaylist * playlist;
    QMediaPlayer * musicPlayer;
    QString path = "C:/Users/Trombonesolo/Documents/JeuTuto/music/";
};

#endif // MUSIC_H
