#include "controller.h"

Controller::Controller(Personnage *personnage, std::vector<std::vector<Case*>> cases, QGraphicsView *plateau)
{
    this->personnage = personnage;
    this->cases = cases;
    this->detection = new Detection();
    this->partie = new Partie(personnage, cases, plateau);
    this->plateau = plateau;
    timer = new QTimer();
    timer_avancer = new QTimer();
    timer_droite = new QTimer();
    timer_gauche = new QTimer();

    QObject::connect( timer,SIGNAL(timeout()), this, SLOT(controlCartes()));
    QObject::connect( timer_avancer,SIGNAL(timeout()),this,SLOT(avancerAnimation()) );
    QObject::connect( timer_droite,SIGNAL(timeout()),this,SLOT(droiteAnimation()) );
    QObject::connect( timer_gauche,SIGNAL(timeout()),this,SLOT(gaucheAnimation()) );

    mutex == false;
    currentPix = 0;
}

Controller::~Controller()
{
    delete personnage;
    delete partie;
    delete detection;
    delete plateau;
    delete timer;
    delete timer_gauche;
    delete timer_droite;
    delete timer_avancer;
    for(unsigned int i =0; i<labels.size();i++){
        delete labels.at(i);
    }

    for(unsigned int i =0; i<cases.size();i++){
        for(unsigned int j=0 ; j<cases.at(i).size(); j++)
            delete cases.at(i).at(j);
    }
}

void Controller::start()
{
    personnage->setTransformOriginPoint(personnage->boundingRect().center());
//    personnage->setOffset(personnage->transformOriginPoint());
    partie->newPartie();

    timer->start(300);


}

//  fonction pour controler le personnage en fonction des cartes captees
void Controller::controlCartes()
{    
//    while(mutex==true);
    std::vector<Carte*> cartes = detection->launch();

    //  pour changer de niveau
    for(unsigned int i = 0; i<cartes.size(); i++){
        if(cartes.at(i)->getId() == 1){
            Message *message = new Message(3);
            message->setText("Niveau suivant..");
            CenterWidgets(message);
            message->exec();
            partie->nextLevel();
            partie->newPartie();
        }
        else if (cartes.at(i)->getId() == 3){
            Message *message = new Message(3);
            message->setText("Niveau précédent..");
            CenterWidgets(message);
            message->exec();
            partie->previousLevel();
            partie->newPartie();
        }
    }


    displayFunctions(cartes);
    if(!cartes.empty()){
        if(cartes.back()->getId()==15){

            controlPersonnage(cartes, 0,1);

            if(checkWin(cases)){
                Message *message = new Message(5);
                message->setText("Victoire !");
                CenterWidgets(message);
                message->exec();
                partie->nextLevel();
                partie->newPartie();
            }
//            usleep(500000);
                partie->newPartie();
                qApp->processEvents();


        }
    }

}

inline void Controller::CenterWidgets(QWidget *widget, QWidget *host) {
    if (!host)
        host = widget->parentWidget();

    if (host) {
        auto hostRect = host->geometry();
        widget->move(hostRect.center() - widget->rect().center());
    }
    else {
        QRect screenGeometry = QApplication::desktop()->screenGeometry();
        int x = (screenGeometry.width() - widget->width()) / 2;
        int y = (screenGeometry.height() - widget->height()) / 2;
        widget->move(x, y);
    }
}

unsigned int Controller::controlPersonnage(std::vector<Carte*> cartes, unsigned int loop_begin, unsigned int marqueur)
{

    for(unsigned int i = loop_begin; i<cartes.size();i++){
        //  debut loop
        if(checkWin(cases)) break;
        if(cartes.at(i)->getId() == 9){
            loop_begin = i;


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
    }
    //  compilateur relou
    return 0;
}

void Controller::movePersonnage(std::string const movement)
{
//    usleep(500000);


    if(movement == "avancer"){
        if(checkAvancer()){

            if(!timer_avancer->isActive()){
                timer_avancer->start(3);
                mutex = true;

            }
            qApp->processEvents();
        }
    }
    else if(movement=="droite"){

        if(!timer_droite->isActive()){
            timer_droite->start(3);
            mutex = true;

        }
        qApp->processEvents();
    }

    else if(movement=="gauche"){


        if(!timer_gauche->isActive()){
            timer_gauche->start(3);
            mutex = true;

        }
        qApp->processEvents();
    }
}

void Controller::avancerAnimation()
{

    personnage->avancer();
    currentPix++;
    if(currentPix > plateau->size().width()/8){
        timer_avancer->stop();
        currentPix = 0;
        mutex = false;
    }

}

void Controller::droiteAnimation()
{
    personnage->tourner_droite();
    currentPix++;
    if(currentPix > 89){
        timer_droite->stop();
        currentPix = 0;
        mutex = false;
    }
}

void Controller::gaucheAnimation()
{
    personnage->tourner_gauche();
    currentPix++;
    if(currentPix > 89){
        timer_gauche->stop();
        currentPix = 0;
        mutex = false;
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
    if(personnage->rotation()==0)
    {
        //verif pour pas depasser limite
        if(personnage->pos().y()==0)
            return false;

        //si la case en haut n'est pas une plateforme alors return false
        else if(!cases.at(personnage->pos().y()/(plateau->size().height()/8)-1).at(personnage->pos().x()/(plateau->size().width()/8))->isPlateforme())
            return false;

        else
            return true;
    }
    //  si le perso va a droite
    else if(personnage->rotation()==90)
    {
        //verif pour pas depasser limite
        if(personnage->pos().x() == (plateau->size().width()/8)*7)
            return false;

        //si la case a droite n'est pas une plateforme alors return false
        else if(!cases.at(personnage->pos().y()/(plateau->size().height()/8)).at(personnage->pos().x()/(plateau->size().width()/8)+1)->isPlateforme())
            return false;

        else
            return true;
    }
    //  si le perso va en bas
    else if(personnage->rotation()==180)
    {
        //verif pour pas depasser limite
        if(personnage->pos().y()== (plateau->size().height()/8)*7)
            return false;

        //si la case en bas n'est pas une plateforme alors return false
        else if(!cases.at(personnage->pos().y()/(plateau->size().height()/8)+1).at(personnage->pos().x()/(plateau->size().width()/8))->isPlateforme())
            return false;

        else
            return true;
    }
    //  si le perso va a gauche
    else if(personnage->rotation()==270)
    {
        //verif pour pas depasser limite
        if(personnage->pos().x()==0)
            return false;

        //si la case a gauche n'est pas une plateforme alors return false
        else if(!cases.at(personnage->pos().y()/(plateau->size().height()/8)).at(personnage->pos().x()/(plateau->size().width()/8)-1)->isPlateforme())
            return false;

        else
            return true;
    }
    //  compilateur relou
    return false;
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



