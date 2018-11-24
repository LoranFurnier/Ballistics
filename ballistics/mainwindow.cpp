#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GameWindow = new Game();
    connect(GameWindow, &Game::firstWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event){
    QPixmap main_bg(":/images/cloud.png");
    QPainter painter(this);
    painter.drawPixmap(0,0,1280,720,main_bg);
    Q_UNUSED(event);
}

void MainWindow::on_exit_button_clicked()
{
    exit(0);
}

void MainWindow::on_vs_person_clicked()
{
    this->close();
    GameWindow->show();
    GameWindow->playDuel();
}
