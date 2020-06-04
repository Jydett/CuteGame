#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QGraphicsScene>
#include <QScrollBar>
#include <QTimer>
#include <QString>
#include <QGraphicsItem>

class PlayScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PlayScene(QString path);
    void loadLevel(const QJsonObject& data);
    void stopTimer();

    static bool showBoundingBoxes;

    static int randInt(int low, int high) {
        return qrand() % ((high + 1) - low) + low;
    }

public slots:
    void doNextLevel();

signals:
    void changeLevel();

private:
    QTimer * timer;
};

#endif // PLAYSCENE_H
