#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QGraphicsScene>
#include <QScrollBar>
#include <QTimer>
#include <QString>
#include <QGraphicsItem>

class PlayScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PlayScene();
    void load(QString path);
    void loadLevel(const QJsonObject& data);

    static bool showBoundingBoxes;

    static int randInt(int low, int high) {
        return qrand() % ((high + 1) - low) + low;
    }

    void display();
    void stop();

public slots:
    void doNextLevel();

signals:
    void changeLevel();

public Q_SLOTS:
    void advanceTest();

private:
    QTimer * timer;
    bool displayed = false;
    bool stopFrame = false;
};

#endif // PLAYSCENE_H
