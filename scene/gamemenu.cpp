#include "gamemenu.h"

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
    scene->invalidate();
    this->hide();
    //add a view
    LevelView * view = new LevelView;
//    view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    PlayScene * scene = new PlayScene();
    view->setScene(scene);
    view->setSceneRect(0, 0, 100000000, 100000000);

    //add the music
    Music * music = new Music();
    music->playMusic(2);

    //create an vieable item
    Player * player = new Player(view);

    //add the item to the scene
    //make the player focusable -> mendatory to get key events
    scene->addItem(player);

    view->centerOn(200, 400);
    view->show();
}


