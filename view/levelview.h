#ifndef VIEW_H
#define VIEW_H

#include "../core/keyboardstatus.h"
#include <QGraphicsView>

class LevelView : public QGraphicsView {
    Q_OBJECT
signals:
    void sceneChanged();

public:
//    QMediaPlaylist *bgm;

    LevelView();
    ~LevelView();
    void sceneSet(QGraphicsScene * scene);
    KeyBoardStatus* keyboardStatus;

protected:
    void wheelEvent(QWheelEvent *e) override;
    bool focusNextPrevChild(bool next) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // VIEW_H
