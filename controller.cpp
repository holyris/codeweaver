#include "controller.h"

Controller::Controller(Personnage *personnage, std::vector<std::vector<Case*>> cases, Detection *detection)
{
    this->personnage = personnage;
    this->cases = cases;
    this->detection = detection;
}

Controller::~Controller()
{
    this->cases.clear();
}


void Controller::controlCartes(std::vector<Carte *> cartes)
{

    for(unsigned int i = 1; i<cartes.size()-1;i++){
        // pour avoir en memoire l'ancienne position du personnage
        int x = personnage->getX();
        int y = personnage->getY();

        if(cartes.at(i)->getId()==13 || cartes.at(i)->getId()==10){
            personnage->avancer();
        }
        this->cases.at(y).at(x)->setPersonnage(false);
        this->cases.at(personnage->getY()).at(personnage->getX())->setPersonnage(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    }
}

void Controller::keyPressEvent(QKeyEvent* event) {

    int x = personnage->getX();
    int y = personnage->getY();
    if(event->key()==Qt::Key_Up){
        personnage->avancer();
    }

    else if(event->key()==Qt::Key_Right)
        personnage->tourner_droite();

    else if(event->key()==Qt::Key_Left)
        personnage->tourner_gauche();

    this->cases.at(y).at(x)->setPersonnage(false);
    this->cases.at(personnage->getY()).at(personnage->getX())->setPersonnage(true);


}


