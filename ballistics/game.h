#ifndef GAME_H
#define GAME_H

#include "libs.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    QPixmap rotor(int a, QPixmap pix, bool isLeft);
    void playDuel();
    void setWind();

signals:
    void firstWindow();  // Сигнал для первого окна на открытие

private slots:
    // Слот-обработчик нажатия кнопки
    void on_endButton_clicked();
    void paintEvent(QPaintEvent *event);

    void on_slider_angle_valueChanged(int value);
    void on_slider_mass_valueChanged(int value);
    void on_slider_power_valueChanged(int value);

    void on_fire_button_clicked();

    void on_slider_angle_2_valueChanged(int value);
    void on_slider_mass_2_valueChanged(int value);
    void on_slider_power_2_valueChanged(int value);

    void on_close_info_clicked();

    void hasFlownOut(bool isLeft);
    void win(bool isLeft);

    void on_win_button_clicked();

private:
    Ui::Game *ui;
    bool isPlayingDuel = false;
    bool isFirstTurn = true;
    int wind;
    QTimer timer;
};

#endif // GAME_H
