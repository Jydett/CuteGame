#include "music.h"

Music::Music()
{
    playlist = new QMediaPlaylist;
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    musicPlayer = new QMediaPlayer;
    musicPlayer->setPlaylist(playlist);
}

Music::~Music() {
    delete playlist;
    delete musicPlayer;
}


void Music::playMusic(int volume) {
    playlist->addMedia(QUrl::fromLocalFile(path + "bestMusic.mp3"));
    musicPlayer->setVolume(volume);
    musicPlayer->play();
}
