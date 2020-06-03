#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QGraphicsScene>
#include <QScrollBar>
#include <QTimer>

class PlayScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PlayScene();
    ~PlayScene();
    void loadLevel(const QJsonObject& data);

    static bool showBoundingBoxes;

    static int randInt(int low, int high) {
        return qrand() % ((high + 1) - low) + low;
    }

private:
    QTimer * timer;
};

#endif // PLAYSCENE_H
