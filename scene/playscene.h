#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QGraphicsScene>
#include <QScrollBar>

class PlayScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PlayScene();
    void loadLevel(const QJsonObject& data);

    static bool showBoundingBoxes;

    static int randInt(int low, int high) {
        return qrand() % ((high + 1) - low) + low;
    }
};

#endif // PLAYSCENE_H
