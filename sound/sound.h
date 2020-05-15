#ifndef SOUND_H
#define SOUND_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileInfo>

class Sound
{
public:
    Sound();
    void playMusic(int volume);
    void playSound(int volume);
private:
    QMediaPlaylist *playlist;
    QMediaPlayer* music;
    QMediaPlayer* soundEffect;
};

#endif // SOUND_H
