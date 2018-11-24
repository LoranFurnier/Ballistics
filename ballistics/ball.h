#ifndef BALL_H
#define BALL_H
#include "libs.h"

class Ball : public QLabel
{
    Q_OBJECT
private:
    //начальные параметры
    float mass = 1;
    float force = 0;
    float angle = 0;                              // масса, сила и угол выстрела
    float x_init = 0;
    float y_init = 0;                         // начальное положение, из которого будут стрелять
    float x0 = 0;
    float y0 = 0;                                 // начальное положение шара при нуле
    float x_f = 0;
    float y_f = 0;                               // положение шара в процессе полета
    float diam = 24;                              // диаметр ядра, нужен при полете
    int wind = 0;
    float t = 0;
public:
    Ball(QWidget *parent);
    float getInitX();
    float getInitY();
    void rotor(int a_deg, bool isLeft);
    void setAngle(int a);
    void setMass(int m);
    void setForce(int f);
    void setWind(int w);
    void set0(int x, int y);
    void setInit(int x, int y);
    void setFinal(int x, int y);
signals:
    void hasFlownOut(bool isLeft);
    void win(bool isLeft);
private slots:
    // Отрисовка самого ядра
    void paintEvent(QPaintEvent *event);
public slots:
    void shoot();
};

#endif // BALL_H
