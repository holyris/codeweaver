#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QWidget>
#include <QKeyEvent>
#include <iostream>
#include <unistd.h>
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
    std::vector<std::vector<QLabel*>> labels;
    Detection *detection;
    void resetPlateau();
    void displayFunctions(std::vector<Carte*> cartes);
public:
    Controller(Personnage *personnage, std::vector<std::vector<Case*>> cases, Detection *detection);
    ~Controller();
    void controlCartes();
    void setLabels(std::vector<std::vector<QLabel*>> labels);


};

#endif // CONTROLLER_H
