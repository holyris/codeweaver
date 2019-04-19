#include "mainwindow.h"
#include "detection.h"
#include "gamewindow.h"
#include <QApplication>
#include <QPushButton>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();
    return a.exec();
}
