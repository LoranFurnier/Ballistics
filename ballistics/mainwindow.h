#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "libs.h"
#include <game.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent *event);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exit_button_clicked();
    void on_vs_person_clicked();

private:
    Ui::MainWindow *ui;
    Game *GameWindow;
};

#endif // MAINWINDOW_H
