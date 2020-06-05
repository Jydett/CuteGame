#include "gamemenu.h"

void gameMenu::closeEvent(QCloseEvent *event) {
    emit menuClosed();
}

gameMenu::gameMenu(QWidget *parent, QGraphicsScene* scene) {
    scene->clear();
    this->setAttribute(Qt::WA_DeleteOnClose, true);
}

void gameMenu::displayMainMenu(QGraphicsScene* scene) {
    //game name
    QGraphicsTextItem* gameName = new QGraphicsTextItem(QString("SUPER CORONARIO LEPEN"));
    QFont nameFont("Berlin Sans FB Demi", 30);
    gameName->setFont(nameFont);
    int posXname = this->width() / 2 - gameName->boundingRect().width() / 2;
    int posYname = 10;
    gameName->setPos(posXname, posYname);
    scene->addItem(gameName);

    //create play button
    button* playButton = new button(QString("Play !"));
    int posXplay = this->width() / 2 - playButton->boundingRect().width() / 2;
    int posYplay = 215;
    playButton->setPos(posXplay, posYplay);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    //create quit button
    button* quitButton = new button(QString("Quit"));
    int posXquit = this->width() / 2 - quitButton->boundingRect().width()/2;
    int posYquit = 315;
    quitButton->setPos(posXquit, posYquit);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(closeMenu()));
    scene->addItem(quitButton);
}

void gameMenu::start() {
    emit displayLvlMenu();
}

void gameMenu::closeMenu() {
    emit menuClosed();
}






