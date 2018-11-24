#include "game.h"
#include "cannon.h"
#include "ball.h"
#include "libs.h"
#include "ui_game.h"
Cannon *cannon1, *cannon2;

Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

    ui->left_ball->set0(ui->left_ball->x(), ui->left_ball->y());        // задаем "нулевые" координаты для левого и правого ядер
    ui->right_ball->set0(ui->right_ball->x(), ui->right_ball->y());

    connect(&timer, SIGNAL(timeout()), ui->left_ball, SLOT(shoot()));
    connect(ui->left_ball, SIGNAL(hasFlownOut(bool)), this, SLOT(hasFlownOut(bool)));
    connect(ui->right_ball, SIGNAL(hasFlownOut(bool)), this, SLOT(hasFlownOut(bool)));
    connect(ui->left_ball, SIGNAL(win(bool)), this, SLOT(win(bool)));
    connect(ui->right_ball, SIGNAL(win(bool)), this, SLOT(win(bool)));
}

Game::~Game()
{
    delete ui;
}

void Game::on_endButton_clicked()
{
    this->close();
    emit firstWindow();
}

void Game::paintEvent(QPaintEvent *event){
    //отрисовка фона
    QPixmap grass(":/images/grass.png");
    QPixmap game_bg(":/images/cloud.png");
    QImage arrows(":/images/arrows.png");
    arrows = arrows.scaled(168,30);
    QPainter painter(this);
    painter.drawPixmap(0,0,1280,720,game_bg);
    painter.drawPixmap(0,375,1280,350,grass);
    if (wind>0){
        painter.drawImage(552,20,arrows,0,0,84,30);
    } else if (wind<0){
        painter.drawImage(636,20,arrows,84,0,84,30);
    }
    painter.end();
    Q_UNUSED(event);
}

void Game::on_slider_angle_valueChanged(int value)
{
    ui->angle->setText(QString::number(value) + "°");
    cannon1->rotor(-value, true);
    ui->left_ball->rotor(-value, true);
    ui->left_ball->setAngle(value);
}

void Game::on_slider_mass_valueChanged(int value)
{
    ui->mass->setText(QString::number(value) + " кг");
    ui->left_ball->setMass(value);
}

void Game::on_slider_power_valueChanged(int value)
{
    ui->power->setText(QString::number(value) + " ед.");
    ui->left_ball->setForce(value);
}

void Game::on_fire_button_clicked()                                             // срабатывает при нажатии кнопки "Огонь"
{
    timer.setInterval(25);                                                      // координаты обновляются 40 раз в секунду
    if(isFirstTurn){                                                            // если ходит игрок слева, то:
        ui->left_ball->setInit(ui->left_ball->x(), ui->left_ball->y());         // задаем начальную точку, откуда отсчитываются координаты
        disconnect(&timer, SIGNAL(timeout()), ui->right_ball, SLOT(shoot()));   // правое ядро никуда не летит, так что "разъединяем"
        connect(&timer, SIGNAL(timeout()), ui->left_ball, SLOT(shoot()));       // левое - наоборот
        timer.start();                                                          // запускаем таймер - ядро начинает полет
        ui->frame_left->setDisabled(true);                                      // игрок слева не может менять характеристики в полете, ибо это напрямую влияет на дальнейший маршрут
        ui->frame_right->setDisabled(false);                                    // а игрок справа может готовиться к полету своего ядра сколько угодно
    } else if (!isFirstTurn){                                                   // если ходит игрок справа, проделываем то же, то наоборот
        ui->right_ball->setInit(ui->right_ball->x(), ui->right_ball->y());
        disconnect(&timer, SIGNAL(timeout()), ui->left_ball, SLOT(shoot()));
        connect(&timer, SIGNAL(timeout()), ui->right_ball, SLOT(shoot()));
        timer.start();
        ui->frame_right->setDisabled(true);
        ui->frame_left->setDisabled(false);
    }
}

void Game::setWind(){
    // делаем ветер
    int low = -30;  // от -30
    int high = 30;  // до 30 метров в секунду
    srand(time(0)); // чтобы случайные числа были более случайны
    wind = rand() % ((high + 1) - low) + low;
    ui->wind->setTextFormat(Qt::RichText);
    ui->wind->setText("<center>" + QString::number(abs(wind)) + " м/с</center>");
    ui->left_ball->setWind(wind);
    ui->right_ball->setWind(wind);
    this->update();
}

void Game::playDuel(){
    if(!isPlayingDuel){
        cannon1=new Cannon(ui->cannon_first);
        QImage im1(":/images/cannon_1_small.png");
        cannon1->setPixmap(QPixmap::fromImage(im1));
        QRect rc;
        rc.setX(0);
        rc.setY(0);
        rc.setWidth(im1.width());
        rc.setHeight(im1.height());
        cannon1->setGeometry(rc);
        cannon1->rotor(0, true);
        cannon1->show();

        cannon2=new Cannon(ui->cannon_second);
        cannon2->setPixmap(QPixmap::fromImage(im1.mirrored(1,0)));
        cannon2->setGeometry(rc);
        cannon2->show();

        ui->fire_button->setStyleSheet("border: none; border-radius: 45px; color: white; background: none; background-color: rgb(220, 25, 0);");

        ui->win_widget->close();
        isPlayingDuel = true;
        isFirstTurn = true;
        ui->frame_left->setDisabled(false);
        ui->frame_right->setDisabled(true);
        setWind();
    }
}

void Game::on_slider_angle_2_valueChanged(int value)
{
    ui->angle_2->setText(QString::number(value) + "°");
    cannon2->rotor(value, false);
    ui->right_ball->rotor(value, false);
    ui->right_ball->setAngle(value);
}

void Game::on_slider_mass_2_valueChanged(int value)
{
    ui->mass_2->setText(QString::number(value) + " кг");
    ui->right_ball->setMass(value);
}

void Game::on_slider_power_2_valueChanged(int value)
{
    ui->power_2->setText(QString::number(value) + " ед.");
    ui->right_ball->setForce(value);
}

void Game::on_close_info_clicked()
{
    ui->info->close();
}

void Game::hasFlownOut(bool isLeft){
    timer.stop();
    if(isLeft){
        ui->fire_button->setStyleSheet("border: none; border-radius: 45px; color: white; background: none; background-color: rgb(0, 85, 255);");
        ui->left_ball->move(ui->left_ball->getInitX(), ui->left_ball->getInitY());
        isFirstTurn = false;
        setWind();                                                                  // после выстрела ветер меняется
    } else if (!isLeft){
        ui->fire_button->setStyleSheet("border: none; border-radius: 45px; color: white; background: none; background-color: rgb(220, 25, 0);");
        ui->right_ball->move(ui->right_ball->getInitX(), ui->right_ball->getInitY());
        isFirstTurn = true;
        setWind();                                                                  // после выстрела ветер меняется
    }
}

void Game::win(bool isLeft){
    timer.stop();
    if(isLeft){
        ui->win_text->setText("<center>Победил игрок с красной пушкой! Поздравляю!</center>");
        ui->win_widget->show();
    } else {
        ui->win_text->setText("<center>Победил игрок с синей пушкой! Поздравляю!</center>");
        ui->win_widget->show();
    }
}

void Game::on_win_button_clicked()
{
    delete cannon1;
    delete cannon2;
    ui->slider_angle->setValue(0);
    ui->slider_angle_2->setValue(0);
    ui->slider_mass->setValue(1);
    ui->slider_mass_2->setValue(1);
    ui->slider_power->setValue(0);
    ui->slider_power_2->setValue(0);
    ui->win_widget->close();
    this->close();
    isPlayingDuel = false;
    emit firstWindow();
}
