#ifndef SOUND_H
#define SOUND_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileInfo>
#include <QSound>

class Sound
{
public:
    Sound();
    ~Sound();
    void playSound(int soundNumber, int volume);

private:
    QMediaPlayer * soundPlayer;
    QMediaPlaylist * playlist;
    QString path = "C:/Users/Trombonesolo/Documents/JeuTuto/sounds/";
};

//Sound::soundPlayer = new QMediaPlayer;
//        this->playlist = new QMediaPlaylist;
//        playlist->addMedia(QUrl::fromLocalFile(path + "jump.wav"));
//        playlist->addMedia(QUrl::fromLocalFile(path + "coin.wav"));
//        playlist->addMedia(QUrl::fromLocalFile(path + "breakingBlock.wav"));
//        playlist->addMedia(QUrl::fromLocalFile(path + "pain.wav"));
//        playlist->addMedia(QUrl::fromLocalFile(path + "plop.mp3"));
//        playlist->addMedia(QUrl::fromLocalFile(path + "finishLvl.wav"));
//        playlist->addMedia(QUrl::fromLocalFile(path + "mask.mp3"));
//        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
//        soundPlayer->setPlaylist(playlist);

#endif // SOUND_H
