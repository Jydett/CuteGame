#include "sound.h"

Sound::Sound() {
    this->soundPlayer = new QMediaPlayer;
    this->playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl::fromLocalFile(path + "jump.wav"));
    playlist->addMedia(QUrl::fromLocalFile(path + "coin.wav"));
    playlist->addMedia(QUrl::fromLocalFile(path + "breakingBlock.wav"));
    playlist->addMedia(QUrl::fromLocalFile(path + "pain.wav"));
    playlist->addMedia(QUrl::fromLocalFile(path + "plop.mp3"));
    playlist->addMedia(QUrl::fromLocalFile(path + "finishLvl.wav"));
    playlist->addMedia(QUrl::fromLocalFile(path + "mask.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    soundPlayer->setPlaylist(playlist);
}

Sound::~Sound() {
    delete playlist;
    delete soundPlayer;
}

void Sound::playSound(int soundNumber,int volume) {
    playlist->setCurrentIndex(soundNumber);
    soundPlayer->setVolume(volume);
    soundPlayer->play();
}
