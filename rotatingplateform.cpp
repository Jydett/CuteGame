#include "rotatingplateform.h"

RotatingPlateform::RotatingPlateform()
{
    angle = 0;
    timer = -1;
    setRect(-400, 150, 300, 20);
    setTransformOriginPoint(boundingRect().center());
    setRotation(30);
}


void RotatingPlateform::advance(int phase) {
    if (! phase)
        return;
//    angle = angle + 0.3;
//    setRotation(angle);
//        QTransform txf = QTransform();
//        txf.translate(this->boundingRect().width()/2, 0);
//        txf.rotate(angle++, Qt::YAxis);
//        txf.translate(-this->boundingRect().width()/2, 0);
//        setTransform(txf, false);
//    }
}

