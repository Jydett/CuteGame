#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QObject>

#include "scene/gamemenu.h"



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    gameMenu* menu = new gameMenu();
    menu->show();
    menu->displayMainMenu();


    return a.exec();
}
