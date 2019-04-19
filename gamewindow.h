#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include "case.h"
#include "personnage.h"
#include "controller.h"
#include "detection.h"
#include "carte.h"
class GameWindow : public QWidget
{

private:
    Controller *controller;
    Detection *detection;

    void keyPressEvent(QKeyEvent *event);

public:
    GameWindow();
    ~GameWindow();



};

#endif // GAMEWINDOW_H
