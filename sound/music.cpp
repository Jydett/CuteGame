#include "music.h"

Music::Music()
{
    playlist = new QMediaPlaylist;
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    musicPlayer = new QMediaPlayer;
    musicPlayer->setPlaylist(playlist);

}

Music::~Music(){
    delete playlist;
    delete musicPlayer;
}

void Music::playMusic(int volume) {
//    playlist->addMedia(QUrl("https://v6p9d9t4.ssl.hwcdn.net/html/1708648/html5game/a_music_loop.mp3"));
    playlist->addMedia(QUrl::fromLocalFile(path + "bestMusic.mp3"));
    musicPlayer->setVolume(volume);
    musicPlayer->play();
}
