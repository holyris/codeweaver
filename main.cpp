#include "detection.h"
#include "gamewindow.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();
    return a.exec();
}
