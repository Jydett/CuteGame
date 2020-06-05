#include "levelmenu.h"
#include "view/gamemenu.h"

void LevelMenu::closeEvent(QCloseEvent *event) {
    emit lvlMenuClosed();
}

LevelMenu::LevelMenu(QWidget *parent, QGraphicsScene* scene) {
    scene->clear();
    this->setAttribute(Qt::WA_DeleteOnClose, true);
}


void LevelMenu::displayLevelMenu(QGraphicsScene* scene) {
    QGraphicsTextItem* title = new QGraphicsTextItem(QString("Choisissez un niveau"));
    QFont nameFont("Consolas", 30);
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

    button* level4 = new button(QString("Level 4"));
    int posXl4 = this->width()/2 - level4->boundingRect().width()/2;
    int posYl4 = 350;
    level4->setPos(posXl4, posYl4);
    connect(level4, SIGNAL(clicked()), this, SLOT(startLevel4()));
    scene->addItem(level4);

    button* level5 = new button(QString("Level 5"));
    int posXl5 = this->width()/2 - level5->boundingRect().width()/2;
    int posYl5 = 410;
    level5->setPos(posXl5, posYl5);
    connect(level5, SIGNAL(clicked()), this, SLOT(startLevel5()));
    scene->addItem(level5);

    button* levelF = new button(QString("Final Level"));
    int posXlF = this->width()/2 - levelF->boundingRect().width()/2;
    int posYlF = 470;
    levelF->setPos(posXlF, posYlF);
    connect(levelF, SIGNAL(clicked()), this, SLOT(startLevelF()));
    scene->addItem(levelF);

    button* retour = new button(QString("Revenir au menu"));
    int posXlr = this->width()/2 - retour->boundingRect().width()/2;;
    int posYlr = 700;
    retour->setPos(posXlr, posYlr);
    connect(retour, SIGNAL(clicked()), this, SLOT(retour()));
    scene->addItem(retour);
}

void LevelMenu::startLevel1() {
    emit displayLevel1();
}


void LevelMenu::startLevel2() {
    emit displayLevel2();
}

void LevelMenu::startLevel3() {
    emit displayLevel3();
}

void LevelMenu::startLevel4() {
    emit displayLevel4();
}

void LevelMenu::startLevel5() {
    emit displayLevel5();
}

void LevelMenu::startLevelF() {
    emit displayLevelF();
}

void LevelMenu::retour() {
    emit returnToMainMenu();
}
