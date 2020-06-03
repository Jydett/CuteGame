#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QString>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsView>

#include <QTimer>

#include <button.h>
#include "scene/playscene.h"
#include "view/levelview.h"
#include "player/player.h"
#include "sound/music.h"

class gameMenu: public QGraphicsView{
    Q_OBJECT
public:
    gameMenu(QWidget* parent = NULL);
    void displayMainMenu();

public slots:
    void start();

private:
    QGraphicsScene* scene;
};

#endif // GAMEMENU_H
