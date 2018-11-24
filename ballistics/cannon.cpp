#include "cannon.h"
QPixmap *mem_pix;
bool isFlipped = false;

Cannon::Cannon(QWidget *parent) : QLabel(parent){}

void Cannon::rotor(int a, bool isLeft)
{
    if (mem_pix==0) mem_pix = new QPixmap(*this->pixmap());
    QPixmap p(rotation(a, *mem_pix, isLeft));
    if (isLeft == false){
        if (isFlipped == false){
            *mem_pix = mem_pix->transformed(QTransform().scale(-1,1).translate(mem_pix->width(), 0));
        }
        isFlipped = true;
    } else {
        if (isFlipped == true){
            *mem_pix = mem_pix->transformed(QTransform().scale(-1,1).translate(mem_pix->width(), 0));
        }
        isFlipped = false;
    }
    QSize sz;
    QRect rc;
    QPoint pn;
    rc=this->geometry();
    pn.setX(rc.x()+rc.width()/2);
    pn.setY(rc.y()+rc.height()/2);
    sz=p.size();
    rc.setWidth(sz.width());
    rc.setHeight(sz.height());
    this->setGeometry(rc);
    this->setPixmap(p);
}

QPixmap Cannon::rotation(int a, QPixmap pix, bool isLeft)
{
    int xc;
    int yc = 95;
    if(isLeft) xc = 95; else xc = 80;
    QSize sz=pix.size();
    QPixmap canv_pix(sz*2);
    canv_pix.fill(Qt::transparent); // залить пустотой
    // центр холста
    int x=0;
    int y=0;
    QPainter p(&canv_pix);
    p.translate(xc,yc);
    p.rotate(a);
    p.translate(-xc,-yc);
    p.drawPixmap(x/2,y/2, pix);
    p.end();
    return canv_pix;
}
