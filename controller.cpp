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
        movePersonnage(cartes, 0);
        usleep(500000);
        bool checkWin=true;
        for(unsigned int i=0; i<cases.size();i++){
            for(unsigned int j=0; j<cases.at(i).size();j++){
                if(cases.at(i).at(j)->isCristal()) checkWin=false;
            }
        }
        if(checkWin) break;
        this->resetPlateau();


    }
}



void Controller::movePersonnage(std::vector<Carte*> cartes, unsigned int loop_begin)
{
    for(unsigned int i = loop_begin; i<cartes.size();i++){
        usleep(400000);

        // pour avoir en memoire la position du personnage avant le mouvement
        int x = personnage->getX();
        int y = personnage->getY();

        //  debut loop
        if(cartes.at(i)->getId() == 9){
            loop_begin = i;

            if(cartes.at(i)->getArgumentId()==11){
                for(unsigned int j=0; j<2;j++) movePersonnage(cartes, loop_begin);
            }
            else if(cartes.at(i)->getArgumentId()==14){
                for(unsigned int j=0; j<3;j++) movePersonnage(cartes, loop_begin);
            }
            else if(cartes.at(i)->getArgumentId()==4){
                for(unsigned int j=0; j<4;j++) movePersonnage(cartes, loop_begin);
            }
            movePersonnage(cartes, loop_begin+1);

        }
        //  fin loop
        else if(cartes.at(i)->getId() == 8){
            break;
        }
        //  avancer
        else if(cartes.at(i)->getId() == 13){
            personnage->avancer();
            if(cartes.at(i)->getArgumentId()==11){
                for(unsigned int j=0; j<1;j++) movePersonnage(cartes, i--);
            }
            else if(cartes.at(i)->getArgumentId()==14){
                for(unsigned int j=0; j<2;j++) movePersonnage(cartes, i--);
            }
            else if(cartes.at(i)->getArgumentId()==4){
                for(unsigned int j=0; j<3;j++) movePersonnage(cartes, i--);
            }


            //changement de la case ou le perso etait ainsi que celle ou il va
            this->cases.at(y).at(x)->setPersonnage(false); // setPersonnage repaint la case en meme temps
            this->cases.at(personnage->getY()).at(personnage->getX())->setDirection(personnage->getDirection());
            this->cases.at(personnage->getY()).at(personnage->getX())->setPersonnage(true);
        }
        //  tourner a droite
        else if(cartes.at(i)->getId() == 7)
        {
            personnage->tourner_droite();
            if(cartes.at(i)->getArgumentId()==11)
            {
                for(unsigned int j=0; j<1;j++) movePersonnage(cartes, i--);
            }
            this->cases.at(personnage->getY()).at(personnage->getX())->setDirection(personnage->getDirection());
        }

        //  tourner a gauche
        else if(cartes.at(i)->getId() == 10)
        {
            personnage->tourner_gauche();
            if(cartes.at(i)->getArgumentId()==11){
                for(unsigned int j=0; j<1;j++) movePersonnage(cartes, i--);
            }
            this->cases.at(personnage->getY()).at(personnage->getX())->setDirection(personnage->getDirection());

        }
        //  interagir
        else if(cartes.at(i)->getId() == 12)
        {
            this->cases.at(personnage->getY()).at(personnage->getX())->setCristal(false);
        }
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

//  pour afficher les fonctions dans l'ordre des cartes
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

//  pour recuperer les labels a modifier
void Controller::setLabels(std::vector<std::vector<QLabel*>> labels){
    this->labels = labels;
}


//  utile pour tester sans les trackers
void Controller::controlKeys(std::vector<Carte*> cartes)
{
    while(1){
        displayFunctions(cartes);
        movePersonnage(cartes, 0);
        usleep(500000);
        this->resetPlateau();

    }
}

//  utile pour tester sans les trackers
void Controller::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_S)
        cartes.push_back(new Carte(16,"function"));
    else if(event->key()==Qt::Key_G)
        cartes.push_back(new Carte(15,"function"));
    else if(event->key()==Qt::Key_Up)
        cartes.push_back(new Carte(13,"function"));
    else if(event->key()==Qt::Key_Left)
        cartes.push_back(new Carte(10,"function"));
    else if(event->key()==Qt::Key_Right)
        cartes.push_back(new Carte(7,"function"));
    else if(event->key()==Qt::Key_I)
        cartes.push_back(new Carte(12,"function"));
    else if(event->key()==Qt::Key_L)
        cartes.push_back(new Carte(9,"function"));
    else if(event->key()==Qt::Key_M)
        cartes.push_back(new Carte(8,"function"));
    else if(event->key()==Qt::Key_Backspace)
        controlKeys(cartes);


}



