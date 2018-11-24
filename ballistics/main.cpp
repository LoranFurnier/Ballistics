#include "mainwindow.h"
#include "game.h"
#include "libs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //блок посвящен открытию и применению файла стилей qss
    QFile styleF;
    styleF.setFileName(":/qss/style.css");
    styleF.open(QFile::ReadOnly);
    QString qssStr = styleF.readAll();
    a.setStyleSheet(qssStr);

    MainWindow w;
    w.show();
    return a.exec();
}
