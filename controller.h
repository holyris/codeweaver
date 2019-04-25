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
#include <partie.h>

class Controller: QWidget
{
private:
    Personnage *personnage;
    std::vector<std::vector<Case*>> cases;
    std::vector<QLabel*> labels;
    Partie *partie;
    Detection *detection;
    void resetPlateau();
    void displayFunctions(std::vector<Carte*> cartes);
    unsigned int controlPersonnage(std::vector<Carte*> cartes, unsigned int loop_begin, unsigned int marqueur);
    void movePersonnage(std::string movement);
    void controlKeys(std::vector<Carte*> cartes);
    bool checkAvancer();

public:
    Controller(Personnage *personnage, std::vector<std::vector<Case*>> cases);
    ~Controller();
    void controlCartes();
    void setLabels(std::vector<QLabel*> labels);
//    void keyPressEvent(QKeyEvent* event);


};

#endif // CONTROLLER_H
