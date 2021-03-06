#include "mainview.h"
#include <QDebug>

MainView::MainView() {
    // create the scene
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024, 768);

    scene = new QGraphicsScene();
    scene->setSceneRect(100000000, 100000000, 0, 0);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
}

void MainView::closeEvent(QCloseEvent *event) {
    qDebug() << "close event";

    delete(this);
}

void MainView::startLvlMenu() {
    qDebug() << "start lvl menu";

    //create lvl menu
    this->menu->hide();
    lvlMenu = new LevelMenu(nullptr, scene);
    lvlMenu->setWindowTitle("Super corona lepen");
    lvlMenu->displayLevelMenu(scene);

    //connect lvl menu signals
    connect(this->lvlMenu, SIGNAL(displayLevel1()), this, SLOT(startLevel1()));
    connect(this->lvlMenu, SIGNAL(displayLevel2()), this, SLOT(startLevel2()));
    connect(this->lvlMenu, SIGNAL(displayLevel3()), this, SLOT(startLevel3()));
    connect(this->lvlMenu, SIGNAL(displayLevel4()), this, SLOT(startLevel4()));
    connect(this->lvlMenu, SIGNAL(displayLevel5()), this, SLOT(startLevel5()));
    connect(this->lvlMenu, SIGNAL(displayLevelF()), this, SLOT(startLevelF()));
    connect(this->lvlMenu, SIGNAL(returnToMainMenu()), this, SLOT(backToMenu()));
    connect(this->lvlMenu, SIGNAL(lvlMenuClosed()), this, SLOT(closeLvlMenu()));
    game = new PlayScene();

    connect(this->game, SIGNAL(changeLevel()), this, SLOT(nextLevel()));
}

void MainView::start(QString path) {
    qDebug() << "start a level";

    this->hide();

    //add a view
    lvlView = new LevelView();
    lvlView->setWindowTitle("Super corona lepen");
    lvlView->setScene(game);
    lvlView->setSceneRect(0, 0, 100000000, 100000000);
    game->load(path);
    //create an vieable item
    player = new Player(lvlView);

    //add the item to the scene
    //make the player focusable -> mendatory to get key events
    game->addItem(player);

    lvlView->centerOn(200, 400);

    // connect signals
    connect(this->lvlView, SIGNAL(lvlViewClosed()), this, SLOT(closeLvlView()));

    game->display();
    lvlView->show();
}

void MainView::display() {
    //background
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    setScene(scene);
    scene->setBackgroundBrush(brush);

    // create the main menu
    menu = new gameMenu(nullptr,scene);
    menu->displayMainMenu(scene);

    //connect game menu signals
    connect(this->menu, SIGNAL(displayLvlMenu()), this, SLOT(startLvlMenu()));
    connect(this->menu, SIGNAL(menuClosed()), this, SLOT(closeMenu()));
}

void MainView::startLevel1() {
    qDebug() << "start level 1";
    lastLevel = 1;
    start(":/levels/level/niveau1.json");
}


void MainView::startLevel2() {
    qDebug() << "start level 2";
    lastLevel = 2;
    start(":/levels/level/niveau2.json");
}

void MainView::startLevel3() {
    qDebug() << "start level 3";
    lastLevel = 3;
    start(":/levels/level/niveau3.json");
}

void MainView::startLevel4() {
    qDebug() << "start level 4";
    lastLevel = 4;
    start(":/levels/level/niveau4.json");
}

void MainView::startLevel5() {
    qDebug() << "start level 5";
    lastLevel = 5;
    start(":/levels/level/niveau5.json");
}

void MainView::startLevelF() {
    qDebug() << "start level F";
    lastLevel = 6;
    start(":/levels/level/niveauF.json");
}

void MainView::backToMenu() {
    qDebug() << "back to menu";

    scene->clear();
    this->menu->displayMainMenu(scene);

    this->lvlMenu = nullptr;
}

void MainView::closeMenu() {
    qDebug() << "close menu";

    this->lvlMenu = nullptr;
    this->lvlView = nullptr;
    this->game = nullptr;

    closeEvent(nullptr);
}

void MainView::closeLvlView() {
    qDebug() << "MainView::closeLvlView begin";
    game->stop();
    this->show();
    this->lvlMenu->displayLevelMenu(scene);
}

//todo a enlever
void MainView::closeLvlMenu() {
    qDebug() << "close lvl menu";
}

void MainView::nextLevel() {
    qDebug() << "MainView::nextLevel()";
    switch (lastLevel) {
        case 1 : startLevel2(); break;
        case 2 : startLevel3(); break;
        case 3 : startLevel4(); break;
        case 4 : startLevel5(); break;
        case 5 : startLevelF(); break;
        case 6 : break;
        default: startLevel1();
    }
}


