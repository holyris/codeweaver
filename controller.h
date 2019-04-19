#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QWidget>
#include <QKeyEvent>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <personnage.h>
#include <case.h>
#include <carte.h>
#include <detection.h>
class Controller: QWidget
{
private:
    Personnage *personnage;
    std::vector<std::vector<Case*>> cases;
    Detection *detection;

public:
    Controller(Personnage *personnage, std::vector<std::vector<Case*>> cases, Detection *detection);
    ~Controller();
    void controlCartes(std::vector<Carte*> cartes);
    void keyPressEvent(QKeyEvent* event);
};

#endif // CONTROLLER_H
