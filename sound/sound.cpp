#include "sound.h"

Sound::Sound()
{
    soundPlayer = new QMediaPlayer;
}

Sound::~Sound(){
    delete soundPlayer;
}

void Sound::playSound(int soundNumber,int volume) {
    switch (soundNumber) {
        case 0 :
            soundPlayer->setMedia(QUrl::fromLocalFile(path + "jump.wav"));
            soundPlayer->setVolume(volume);
            soundPlayer->play();
            break;
        case 1 :
            soundPlayer->setMedia(QUrl::fromLocalFile(path + "coin.wav"));
            soundPlayer->setVolume(volume);
            soundPlayer->play();
            break;
        case 2 :
            soundPlayer->setMedia(QUrl::fromLocalFile(path + "breakingBlock.wav"));
            soundPlayer->setVolume(volume);
            soundPlayer->play();
            break;
        case 3 :
            soundPlayer->setMedia(QUrl::fromLocalFile(path + "pain.wav"));
            soundPlayer->setVolume(volume);
            soundPlayer->play();
            break;
        case 4 :
            soundPlayer->setMedia(QUrl::fromLocalFile(path + "plop.mp3"));
            soundPlayer->setVolume(volume);
            soundPlayer->play();
            break;
        case 5 :
            soundPlayer->setMedia(QUrl::fromLocalFile(path + "finishLvl.wav"));
            soundPlayer->setVolume(volume);
            soundPlayer->play();
            break;
        default: break;
    }

}
