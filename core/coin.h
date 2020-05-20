#ifndef COIN_H
#define COIN_H
#include "inert.h"
#include <QPixmap>


class Coin : public Inert
{
public:
    Coin();

private:
    QPixmap textureData;
};

#endif // COIN_H
