#include "controller.h"

Controller::Controller(Personnage *personnage, std::vector<std::vector<Case*>> cases)
{
    this->personnage = personnage;
    this->cases = cases;
    this->detection = new Detection();
    this->partie = new Partie(personnage, cases);

}

Controller::~Controller()
{
    this->cases.clear();
}

//  fonction pour controler le personnage en fonction des cartes captees
void Controller::controlCartes()
{
    partie->newPartie("easy");
    while(1){

        std::vector<Carte*> cartes = detection->launch();
        displayFunctions(cartes);
        if(!cartes.empty()){
            if(cartes.back()->getId()==15){

                controlPersonnage(cartes, 0,1);
                usleep(500000);

                if(checkWin(cases)){
                    Message *message = new Message;

                    message->exec();
                    partie->newPartie("easy");
                }

                this->resetPlateau();
            }
        }

    }
}

unsigned int Controller::controlPersonnage(std::vector<Carte*> cartes, unsigned int loop_begin, unsigned int marqueur)
{
    for(unsigned int i = loop_begin; i<cartes.size();i++){
        //  debut loop
        if(checkWin(cases)) break;
        if(cartes.at(i)->getId() == 9){
            loop_begin = i;
//            std::cout << "i : " << i << "  arg : " << cartes.at(i)->getArgumentId() << std::endl;


            if(cartes.at(i)->getArgumentId()==11){
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);

            }
            else if(cartes.at(i)->getArgumentId()==14){
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);

            }
            else if(cartes.at(i)->getArgumentId()==4){
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);


            }else if(cartes.at(i)->getArgumentId()==5){
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);

            }else if(cartes.at(i)->getArgumentId()==6){
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);

            } else {
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
                i = controlPersonnage(cartes, loop_begin+1,marqueur+1);
            }

        }
        //  fin loop
        else if(cartes.at(i)->getId() == 8){
//            if(marqueur >= 2) break;
            return i;
        }
        //  avancer
        else if(cartes.at(i)->getId() == 13){

            if(cartes.at(i)->getArgumentId()==11){
                movePersonnage("avancer");
                movePersonnage("avancer");

            }
            else if(cartes.at(i)->getArgumentId()==14){
                movePersonnage("avancer");
                movePersonnage("avancer");
                movePersonnage("avancer");

            }
            else if(cartes.at(i)->getArgumentId()==4){
                movePersonnage("avancer");
                movePersonnage("avancer");
                movePersonnage("avancer");
                movePersonnage("avancer");

            }
            else if(cartes.at(i)->getArgumentId()==5){
                movePersonnage("avancer");
                movePersonnage("avancer");
                movePersonnage("avancer");
                movePersonnage("avancer");
                movePersonnage("avancer");
            }
            else if(cartes.at(i)->getArgumentId()==6){
                movePersonnage("avancer");
                movePersonnage("avancer");
                movePersonnage("avancer");
                movePersonnage("avancer");
                movePersonnage("avancer");
                movePersonnage("avancer");
            } 
            else movePersonnage("avancer");
        }
        //  tourner a droite
        else if(cartes.at(i)->getId() == 7)
        {
            if(cartes.at(i)->getArgumentId()==11)
            {
                movePersonnage("droite");
                movePersonnage("droite");
            } else
                movePersonnage("droite");
        }

        //  tourner a gauche
        else if(cartes.at(i)->getId() == 10)
        {
            if(cartes.at(i)->getArgumentId()==11){
                movePersonnage("gauche");
                movePersonnage("gauche");

            } else
                movePersonnage("gauche");
        }
        //  interagir
        else if(cartes.at(i)->getId() == 0)
        {
            usleep(500000);
            this->cases.at(personnage->getY()).at(personnage->getX())->setCristal(false);
        }
    }
}

void Controller::movePersonnage(std::string const movement)
{
    usleep(500000);
    if(movement == "avancer")
    {
        if(checkAvancer()){
            // pour avoir en memoire la position du personnage avant le mouvement
            int const x = personnage->getX();
            int const y = personnage->getY();
            personnage->avancer();
            //changement de la case ou le perso etait ainsi que celle ou il va
            this->cases.at(y).at(x)->setPersonnage(false); // setPersonnage repaint la case en meme temps

            this->cases.at(personnage->getY()).at(personnage->getX())->setDirection(personnage->getDirection());
            this->cases.at(personnage->getY()).at(personnage->getX())->setCristal(false);
            this->cases.at(personnage->getY()).at(personnage->getX())->setPersonnage(true);
        }
    } else if(movement == "droite"){
        personnage->tourner_droite();
        this->cases.at(personnage->getY()).at(personnage->getX())->setDirection(personnage->getDirection());
    }
    else if(movement == "gauche"){
        personnage->tourner_gauche();
        this->cases.at(personnage->getY()).at(personnage->getX())->setDirection(personnage->getDirection());
    }


}

//  reset les cases a leur statut de debut de partie
void Controller::resetPlateau()
{
    personnage->reset();
    for(unsigned int i = cases.size(); i--;){
        for(unsigned int j = cases.at(i).size();j--;){
            cases.at(i).at(j)->reset();
        }
    }
}

//  pour afficher les fonctions dans l'ordre des cartes
void Controller::displayFunctions(std::vector<Carte*> cartes)
{
    //  boucle pour nettoyer les textes
    for(unsigned int i = labels.size();i--;){
        labels.at(i)->setText("");
        if(cartes.empty())
            labels.at(i)->repaint();
    }

    unsigned int n=0;
    for(unsigned int i=0; i<cartes.size();i++)
    {
        QString string = cartes.at(i)->getName();
        if(cartes.at(i)->getType()!="argument"){
            if(cartes.at(i)->getArgumentId()!=-1){
                string = string+"  -  "+cartes.at(i)->getArgumentName();
            }
            n += 2;
            labels.at(n)->setText(string);
            labels.at(n)->repaint();
        }

    }
}

//  pour recuperer les labels a modifier
void Controller::setLabels(std::vector<QLabel*> labels)
{
    this->labels = labels;
}

//  fonction pour verif si le perso peut avancer
bool Controller::checkAvancer()
{
    //  si le personnage va en haut
    if(personnage->getDirection()==0)
    {
        if(personnage->getY()==0)
            return false;

        //si la case en haut n'est pas une plateforme alors return false
        else if(!cases.at(personnage->getY()-1).at(personnage->getX())->isPlateforme())
            return false;

        else
            return true;
    }
    //  si le perso va a droite
    else if(personnage->getDirection()==1)
    {

        if(personnage->getX()==cases.at(0).size()-1)
            return false;

        //si la case a droite n'est pas une plateforme alors return false
        else if(!cases.at(personnage->getY()).at(personnage->getX()+1)->isPlateforme())
            return false;

        else
            return true;
    }
    //  si le perso va en bas
    else if(personnage->getDirection()==2)
    {

        if(personnage->getY()==cases.size()-1)
            return false;

        //si la case en bas n'est pas une plateforme alors return false
        else if(!cases.at(personnage->getY()+1).at(personnage->getX())->isPlateforme())
            return false;

        else
            return true;
    }
    //  si le perso va a gauche
    else if(personnage->getDirection()==3)
    {
        if(personnage->getX()==0)
            return false;

        //si la case a gauche n'est pas une plateforme alors return false
        else if(!cases.at(personnage->getY()).at(personnage->getX()-1)->isPlateforme())
            return false;

        else
            return true;
    }
}

bool Controller::checkWin(std::vector<std::vector<Case *>> cases)
{
    // check si les cristaux sont recuperes
    bool checkWin=true;
    for(unsigned int i=0; i<cases.size();i++){
        for(unsigned int j=0; j<cases.at(i).size();j++){
            if(cases.at(i).at(j)->isCristal()) checkWin=false;
        }
    }
    return checkWin;
}

////  utile pour tester sans les trackers
//void Controller::controlKeys(std::vector<Carte*> cartes)
//{
//    while(1){
//        displayFunctions(cartes);
//        controlPersonnage(cartes, 0,1);
//        usleep(500000);
//        this->resetPlateau();

//    }
//}

////  utile pour tester sans les trackers
//void Controller::keyPressEvent(QKeyEvent *event)
//{
//    if(event->key()==Qt::Key_S)
//        cartes.push_back(new Carte(16,"function"));
//    else if(event->key()==Qt::Key_G)
//        cartes.push_back(new Carte(15,"function"));
//    else if(event->key()==Qt::Key_Up)
//        cartes.push_back(new Carte(13,"function"));
//    else if(event->key()==Qt::Key_Left)
//        cartes.push_back(new Carte(10,"function"));
//    else if(event->key()==Qt::Key_Right)
//        cartes.push_back(new Carte(7,"function"));
//    else if(event->key()==Qt::Key_I)
//        cartes.push_back(new Carte(0,"function"));
//    else if(event->key()==Qt::Key_L)
//        cartes.push_back(new Carte(9,"function"));
//    else if(event->key()==Qt::Key_M)
//        cartes.push_back(new Carte(8,"function"));
//    else if(event->key()==Qt::Key_Backspace)
//        controlKeys(cartes);


//}



