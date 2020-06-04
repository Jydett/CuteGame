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
    QMediaPlayer* soundPlayer;
    QString path = "C:/Users/lenam/Documents/CuteGame/sounds/";
};

#endif // SOUND_H
