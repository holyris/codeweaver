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

//  fonction pour controler le personnage en fonction des cartes captees
void Controller::controlCartes()
{
    while(1){
        detection->launch();
        std::vector<Carte*> cartes = detection->getCartes();
        displayFunctions(cartes);
        unsigned int loop=1;        //  nombre de tours precise par l'argument
        unsigned int loop_begin=1;    //  sert a savoir ou le boucle commence
        unsigned int loop_i=1;      //  iterateur de la boucle
        unsigned int loop_current_carte=0;
        unsigned int loop_current_carte_i=1;
        for(unsigned int i = 1; i<cartes.size()-1;i++){
            usleep(400000);

            // pour avoir en memoire la position du personnage avant le mouvement
            int x = personnage->getX();
            int y = personnage->getY();

            //  debut loop
            if(cartes.at(i)->getId() == 9){
                loop_begin = i;
                if(cartes.at(i)->getArgumentId()==11)
                    loop = 2;
                else if(cartes.at(i)->getArgumentId()==14)
                    loop = 3;
                else if(cartes.at(i)->getArgumentId()==4)
                    loop = 4;
                else loop = 1;

            }

            //  fin loop
            else if(cartes.at(i)->getId() == 8){
                //  si le nb de tour precise par l'arg n'a pas ete atteint
                if(loop_i != loop){
                    loop_i++;
                    i = loop_begin;
                }
            }

            //  avancer
            else if(cartes.at(i)->getId() == 13){
                personnage->avancer();
                if(cartes.at(i)->getArgumentId()==11)
                    loop_current_carte = 2;
                else if(cartes.at(i)->getArgumentId()==14)
                    loop_current_carte = 3;
                else if(cartes.at(i)->getArgumentId()==4)
                    loop_current_carte = 4;
                else loop_current_carte = 1;

                if(loop_current_carte_i != loop_current_carte){
                    i--; //on recommence ce tour
                    loop_current_carte_i++;
                }else{
                    loop_current_carte=0;
                    loop_current_carte_i = 1;
                }

            }

            //  tourner a droite
            else if(cartes.at(i)->getId() == 7)
            {
                personnage->tourner_droite();

                if(cartes.at(i)->getArgumentId()==11)
                    loop_current_carte = 2;
                else loop_current_carte = 1;

                if(loop_current_carte_i != loop_current_carte){
                    i--; //on recommence ce tour
                    loop_current_carte_i++;
                }else{
                    loop_current_carte=0;
                    loop_current_carte_i = 1;
                }
            }

            //  tourner a gauche
            else if(cartes.at(i)->getId() == 10)
            {
                personnage->tourner_gauche();

                if(cartes.at(i)->getArgumentId()==11)
                    loop_current_carte = 2;
                else loop_current_carte = 1;

                if(loop_current_carte_i != loop_current_carte){
                    i--; //on recommence ce tour
                    loop_current_carte_i++;
                }else{
                    loop_current_carte=0;
                    loop_current_carte_i = 1;
                }
            }


            //changement de la case ou le perso etait ainsi que celle ou il va
            this->cases.at(y).at(x)->setPersonnage(false); // setPersonnage repaint aussi la case
            this->cases.at(personnage->getY()).at(personnage->getX())->setDirection(personnage->getDirection()); // pareil
            this->cases.at(personnage->getY()).at(personnage->getX())->setPersonnage(true);
        }
        usleep(500000);
        this->resetPlateau();

    }
}


void Controller::resetPlateau()
{
    personnage->reset();
    for(unsigned int i = 0; i<cases.size(); i++){
        for(unsigned int j = 0; j<cases.at(i).size();j++){
            cases.at(i).at(j)->reset();
        }
    }
}


void Controller::displayFunctions(std::vector<Carte*> cartes)
{
    //  boucle pour nettoyer les textes
    for(unsigned int i = 0; i<labels.size();i++){
        for(unsigned int j = 0; j<labels.at(i).size();j++){
           labels.at(i).at(j)->setText("");
        }
    }
    unsigned int j=0;
    for(unsigned int i=0; i<cartes.size();i++)
    {
        QString string = cartes.at(i)->getName();
        if(cartes.at(i)->getType()!="argument"){
            labels.at(j).at(0)->setText(string);
            if(cartes.at(i)->getArgumentId()!=-1){
                labels.at(j).at(1)->setText(cartes.at(i)->getArgumentName());
            }
            j++;
        }


    }
}

void Controller::setLabels(std::vector<std::vector<QLabel*>> labels){
    this->labels = labels;
}


