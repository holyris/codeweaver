#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QWidget>
#include <QKeyEvent>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/imgproc.hpp>
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
    std::vector<Carte*> cartes;
    Detection *detection;
    void resetPlateau();
    void displayFunctions(std::vector<Carte*> cartes);
    void movePersonnage(std::vector<Carte*> cartes, unsigned int i);
    void controlKeys(std::vector<Carte*> cartes);

public:
    Controller(Personnage *personnage, std::vector<std::vector<Case*>> cases, Detection *detection);
    ~Controller();
    void controlCartes();
    void setLabels(std::vector<std::vector<QLabel*>> labels);
    void keyPressEvent(QKeyEvent* event);

};

#endif // CONTROLLER_H
