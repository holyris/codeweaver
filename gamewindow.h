#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsGridLayout>
#include <QTimer>
#include <QDebug>
#include <QStackedLayout>
#include "case.h"
#include "personnage.h"
#include "controller.h"
#include "detection.h"
#include "carte.h"
#include "partie.h"
class GameWindow : public QWidget
{

private:
    QGraphicsScene *scene;
    Controller *controller;
    Personnage *personnage;
    QGraphicsView *plateau;
    void keyPressEvent(QKeyEvent *event);


public:
    GameWindow();
    ~GameWindow();
    QGraphicsView *view;

};

#endif // GAMEWINDOW_H
