#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QGraphicsView>
#include "scene/levelmenu.h"
#include "scene/gamemenu.h"
#include "scene/playscene.h"
#include "levelview.h"
#include "player/player.h"


class MainView: public QGraphicsView{
    Q_OBJECT
public:
    MainView();
    void start(QString path);
    void display();
private:
    void closeEvent(QCloseEvent *event) override;
public slots:
    void startLvlMenu();
    void startLevel1();
    void startLevel2();
    void startLevel3();
    void startLevel4();
    void startLevel5();
    void startLevelF();
    void backToMenu();
    void closeMenu();
    void closeLvlView();
    void closeLvlMenu();
    void nextLevel();
private:
    gameMenu* menu;
    LevelMenu* lvlMenu;
    PlayScene* game;
    LevelView* lvlView;
    Player* player;
    QGraphicsScene* scene;
    int lastLevel = 0;
};

#endif // MAINVIEW_H
