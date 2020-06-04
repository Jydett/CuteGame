#ifndef VIEW_H
#define VIEW_H

#include "../core/keyboardstatus.h"
#include <QGraphicsView>
#include "sound/music.h"

class LevelView : public QGraphicsView {
    Q_OBJECT

signals:
    void sceneChanged();
    void lvlViewClosed();

private:
    void closeEvent(QCloseEvent *event) override;

public:
//    QMediaPlaylist *bgm;
    LevelView();
    ~LevelView();
    void sceneSet(QGraphicsScene * scene);
    KeyBoardStatus* keyboardStatus;
    void drawForeground(QPainter *painter, const QRectF &rect) override;

protected:
    void wheelEvent(QWheelEvent *e) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Music music;
};

#endif // VIEW_H
