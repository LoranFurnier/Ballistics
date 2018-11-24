#ifndef CANNON_H
#define CANNON_H
#include "libs.h"

class Cannon : public QLabel
{
public:
    Cannon(QWidget *parent);
    void rotor(int a, bool isLeft);
    QPixmap rotation(int a, QPixmap pix, bool isLeft);
};

#endif // CANNON_H
