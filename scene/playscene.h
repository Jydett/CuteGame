#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QGraphicsScene>
#include <QScrollBar>

class PlayScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PlayScene();

    static bool showBoundingBoxes;
};

#endif // PLAYSCENE_H
