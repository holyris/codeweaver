#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>
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
    Q_OBJECT

private:
    Controller *controller;
    Personnage *personnage;
    QGraphicsView *plateau;
    QStackedLayout *stacked_layout;
    QWidget *widget_grille_plateau;
    void keyPressEvent(QKeyEvent *event);



public:
    GameWindow();
    ~GameWindow();
    QGraphicsView *view;


private slots:
    void start();

};

#endif // GAMEWINDOW_H
