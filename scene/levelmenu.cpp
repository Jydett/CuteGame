#include "levelmenu.h"
#include "scene/gamemenu.h"

void LevelMenu::closeEvent(QCloseEvent *event)
{
    gameMenu* menu = new gameMenu();
    menu->show();
    menu->displayMainMenu();
}

LevelMenu::LevelMenu(QWidget *parent)
{
    //create scene
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024, 768);

    scene = new QGraphicsScene();
    scene->setSceneRect(100000000, 100000000, 0, 0);
    setScene(scene);

}


void LevelMenu::displayLevelMenu()
{
    QGraphicsTextItem* title = new QGraphicsTextItem(QString("Choisissez un niveau"));
    QFont nameFont("Consolas",30);
    title->setFont(nameFont);
    int posXtitle = this->width()/2 - title->boundingRect().width()/2;
    int posYtitle = 10;
    title->setPos(posXtitle, posYtitle);
    scene->addItem(title);

    //create each level button
    button* level1 = new button(QString("Level 1"));
    int posXl1 = this->width()/2 - level1->boundingRect().width()/2;
    int posYl1 = 170;
    level1->setPos(posXl1, posYl1);
    connect(level1, SIGNAL(clicked()), this, SLOT(startLevel1()));
    scene->addItem(level1);

    button* level2 = new button(QString("Level 2"));
    int posXl2 = this->width()/2 - level2->boundingRect().width()/2;
    int posYl2 = 230;
    level2->setPos(posXl2, posYl2);
    connect(level2, SIGNAL(clicked()), this, SLOT(startLevel2()));
    scene->addItem(level2);

    button* level3 = new button(QString("Level 3"));
    int posXl3 = this->width()/2 - level3->boundingRect().width()/2;
    int posYl3 = 290;
    level3->setPos(posXl3, posYl3);
    connect(level3, SIGNAL(clicked()), this, SLOT(startLevel3()));
    scene->addItem(level3);

    button* levelF = new button(QString("Final Level"));
    int posXlF = this->width()/2 - levelF->boundingRect().width()/2;
    int posYlF = 350;
    levelF->setPos(posXlF, posYlF);
    connect(levelF, SIGNAL(clicked()), this, SLOT(startLevelF()));
    scene->addItem(levelF);
}

void LevelMenu::start(QString path)
{
    this->hide();
    //add a view
    LevelView * view = new LevelView;
//    view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    PlayScene * scene = new PlayScene(path);
    view->setScene(scene);
    view->setSceneRect(0, 0, 100000000, 100000000);

    //create an vieable item
    Player * player = new Player(view);

    //add the item to the scene
    //make the player focusable -> mendatory to get key events
    scene->addItem(player);

    view->centerOn(200, 400);
    view->show();

}

void LevelMenu::startLevel1()
{
    start("C:/Users/lenam/Documents/CuteGame/level/niveau1.json");
}


void LevelMenu::startLevel2()
{
    start("C:/Users/lenam/Documents/CuteGame/level/niveau2.json");
}

void LevelMenu::startLevel3()
{
    start("C:/Users/lenam/Documents/CuteGame/level/niveau3.json");
}


void LevelMenu::startLevelF()
{
    start("C:/Users/lenam/Documents/CuteGame/level/niveauF.json");
}