#include "ball.h"
Ball::Ball(QWidget *parent) : QLabel(parent){}

void Ball::paintEvent(QPaintEvent *event){
    Q_UNUSED (event);
    QPainter p(this);
    p.setBrush(QColor(25,24,25));
    p.setPen(Qt::transparent);
    p.drawEllipse(0,0,this->width(),this->height());
}

void Ball::rotor(int a_deg, bool isLeft)
{
    float a = (float)a_deg*PI/180.0;
    float y, x;
    float xc;
    isLeft ? xc = 145 : xc = 1130;
    float yc = 596;
    if (isLeft){
        x = (x0-xc)*cos(a) - (y0-yc)*sin(a) + xc;
        y = (x0+24-xc)*sin(a) + (y0-yc)*cos(a) + yc;
    } else {
        x = (x0-xc)*cos(a) - (y0+24-yc)*sin(a) + xc;
        y = (x0-xc)*sin(a) + (y0-yc)*cos(a) + yc;
    }
    this->move(x, y);
}

// передает
float Ball::getInitX(){
    return x_init;
}

float Ball::getInitY(){
    return y_init;
}

void Ball::setAngle(int a){
    angle = a;
}

void Ball::setMass(int m){
    mass = m;
};

void Ball::setForce(int f){
    force = f;
}

void Ball::setWind(int w){
    wind = w;
}

void Ball::set0(int x, int y){
    x0 = x;
    y0 = y;
}

void Ball::setInit(int x, int y){
    x_init = x;
    y_init = y;
}

void Ball::setFinal(int x, int y){
    x_f = x;
    y_f = y;
}

void Ball::shoot(){
    double v, vy, vx, k, wspeed;
    // если левое ядро вылетело за пределы экрана
    if ((((x_f+x_init)>1280) || ((y_init-y_f)>720)) && (x_init<=640)){
        t = x_f = y_f = 0;
        emit hasFlownOut(true);
    } else if ((((x_init-x_f)<0) || ((y_init-y_f)>720)) && (x_init>=640)){
        t = x_f = y_f = 0;
        emit hasFlownOut(false);
    } else if (((y_init-y_f)>=550) && ((y_init-y_f)<=650) && x_init<=640 && (x_init+x_f)>=1050 && (x_init+x_f)<=1225){
        t = x_f = y_f = 0;
        this->move(this->getInitX(), this->getInitY());
        emit win(true);
    } else if (((y_init-y_f)>=550) && ((y_init-y_f)<=650) && x_init>=640 && (x_init-x_f)>=50 && (x_init-x_f)<=225){
        t = x_f = y_f = 0;
        this->move(this->getInitX(), this->getInitY());
        emit win(false);
    } else {
        t += 0.005;
        k = 0.24*PI*diam;
        v = force*force/(mass);
        vx = v*cos(angle * PI/180);
        wspeed = k*(vx/100-wind)*0.2;
        x_init<=640 ? vx += wspeed : vx-=wspeed;
        x_f = vx*t;
        vy = v*sin(angle * PI/180)-(t*grav);
        y_f = vy*t;
        if (x_init<=640){
            this->move(x_f+x_init, y_init-y_f); // левое ядро летит направо
        } else {
            this->move(x_init-x_f, y_init-y_f); // правое ядро летит налево
        }
    }
}
