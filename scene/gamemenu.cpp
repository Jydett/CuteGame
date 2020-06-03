#include "gamemenu.h"

void gameMenu::closeEvent(QCloseEvent *event)
{
    delete(this);
}

gameMenu::gameMenu(QWidget *parent)
{
    //create scene
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024, 768);

    scene = new QGraphicsScene();
    scene->setSceneRect(100000000, 100000000, 0, 0);
    setScene(scene);

}

void gameMenu::displayMainMenu()
{
    //game name
    QGraphicsTextItem* gameName = new QGraphicsTextItem(QString("SUPER CORONARIO LEPEN"));
    QFont nameFont("Berlin Sans FB Demi",30);
    gameName->setFont(nameFont);
    int posXname = this->width()/2 - gameName->boundingRect().width()/2;
    int posYname = 10;
    gameName->setPos(posXname, posYname);
    scene->addItem(gameName);

    //create play button
    button* playButton = new button(QString("Play !"));
    int posXplay = this->width()/2 - playButton->boundingRect().width()/2;
    int posYplay = 170;
    playButton->setPos(posXplay, posYplay);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);


    //create quit button
    button* quitButton = new button(QString("Quit"));
    int posXquit = this->width()/2 - quitButton->boundingRect().width()/2;
    int posYquit = 245;
    quitButton->setPos(posXquit, posYquit);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void gameMenu::start()
{
    this->hide();
    LevelMenu* levelMenu = new LevelMenu();
    levelMenu->show();
    levelMenu->displayLevelMenu();
}





