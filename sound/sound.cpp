#include "sound.h"

Sound::Sound()
{
    playlist = new QMediaPlaylist;
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    music = new QMediaPlayer;
    music->setPlaylist(playlist);
    soundEffect = new QMediaPlayer;

}

void Sound::playMusic(int volume) {
    playlist->addMedia(QUrl::fromLocalFile("C:/Users/vlefi/Documents/Polytech 4A/Qt/CuteGame/Video Killed The Radio Star.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("C:/Users/vlefi/Documents/Polytech 4A/Qt/CuteGame/bestMusic.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("C:/Users/vlefi/Documents/Polytech 4A/Qt/CuteGame/Rasputin.mp3"));
    playlist->addMedia(QUrl::fromLocalFile("C:/Users/vlefi/Documents/Polytech 4A/Qt/CuteGame/Take On Me.mp3"));
//    playlist->addMedia(QUrl::fromLocalFile("/bestMusic.mp3"));
//    playlist->addMedia(QUrl::fromLocalFile("/Rasputin.mp3"));
//    playlist->addMedia(QUrl::fromLocalFile("/Take On Me.mp3"));
//    playlist->addMedia(QUrl::fromLocalFile("/Video Killed The Radio Star.mp3"));
    music->setVolume(volume);
    music->play();
}

void Sound::playSound(int volume) {
    soundEffect->setMedia(QUrl::fromLocalFile("C:/Users/vlefi/Documents/Polytech 4A/Qt/CuteGame/jump.wav"));
    soundEffect->setVolume(volume);
    soundEffect->play();
}
