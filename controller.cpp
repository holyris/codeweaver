#include "controller.h"

Controller::Controller(Personnage *personnage, std::vector<std::vector<Case*>> cases, QGraphicsView *plateau)
{
    this->personnage = personnage;
    this->cases = cases;
    this->detection = new Detection();
    this->partie = new Partie(personnage, cases, plateau);
    this->plateau = plateau;
    timer = new QTimer();

    QObject::connect( timer,SIGNAL(timeout()), this, SLOT(controlCartes()) );
    movement = 0;
}

Controller::~Controller()
{
    delete personnage;
    delete partie;
    delete detection;
    delete plateau;
    delete timer;
    for(unsigned int i =0; i<labels.size();i++){
        delete labels.at(i);
    }

    for(unsigned int i =0; i<cases.size();i++){
        for(unsigned int j=0 ; j<cases.at(i).size(); j++)
            delete cases.at(i).at(j);
    }

    for(unsigned int i =0; i<cartes.size();i++){
        delete cartes.at(i);
    }
}

void Controller::start()
{
    partie->newPartie();


    timer->setSingleShot(true);

    timer->start(1000);

    qApp->processEvents();



}

//  fonction pour controler le personnage en fonction des cartes captees
void Controller::controlCartes()
{
    cartes = detection->launch();
    displayFunctions(cartes);

    if(!cartes.empty()) {

        //  pour changer de niveau
        for(unsigned int i = 0; i<cartes.size(); i++){
            if(cartes.at(i)->getId() == 1){
                Message *message = new Message(3);
                message->setText("Niveau suivant");
                CenterWidgets(message);
                message->exec();
                partie->nextLevel();
                partie->newPartie();
            }
            else if (cartes.at(i)->getId() == 3){
                Message *message = new Message(3);
                message->setText("Niveau précédent");
                CenterWidgets(message);
                message->exec();
                partie->previousLevel();
                partie->newPartie();
            }
        }


        if(cartes.back()->getId()!=15){

            timer->start();
            qApp->processEvents();
            return;
        }
    } else {

        timer->start();
        qApp->processEvents();
        return;
    }


    controlPersonnage(0);

    if(checkWin(cases)){
        Message *message = new Message(5);
        message->setText("Victoire !");
        CenterWidgets(message);
        message->exec();
        partie->nextLevel();
        partie->newPartie();
    }
    usleep(500000);
    plateau->update();
    partie->newPartie();
    timer->start();
    return;



}
//  un truc pour soi disant centrer un widget
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

unsigned int Controller::controlPersonnage(unsigned int loop_begin)
{

    for(unsigned int i = loop_begin; i<cartes.size();i++){
        if(checkWin(cases)) break;

        //  debut loop
        if(cartes.at(i)->getId() == 9){
            loop_begin = i;


            if(cartes.at(i)->getArgumentId()==11){
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);

            }
            else if(cartes.at(i)->getArgumentId()==14){
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);

            }
            else if(cartes.at(i)->getArgumentId()==4){
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);


            }else if(cartes.at(i)->getArgumentId()==5){
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);

            }else if(cartes.at(i)->getArgumentId()==6){
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);

            } else {
                i = controlPersonnage(loop_begin+1);
                i = controlPersonnage(loop_begin+1);
            }

        }
        //  fin loop
        else if(cartes.at(i)->getId() == 8){
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
    usleep(200000);

    if(movement == "avancer"){
        if(checkAvancer()){
            this->movement = 0;

        }
        else{
            this->movement = 3;
        }
        animation();
        cases.at(personnage->pos().y()/(plateau->size().height()/8)).at(personnage->pos().x()/(plateau->size().width()/8))->deleteCristal();


    }
    else if(movement=="droite"){
        this->movement = 1;
        animation();
    }

    else if(movement=="gauche"){
        this->movement = 2;
        animation();
    }

}

void Controller::animation()
{
    //avancer
    if(movement == 0){
        for(int i = 0; i<plateau->size().height()/8;i++){
            usleep(2000);
//            cases.at(personnage->pos().y()/(plateau->size().height()/8)).at(personnage->pos().x()/(plateau->size().width()/8))->deleteCristal();

            //faire disparaite le cristal au bon moment
//            if(i>plateau->size().height()/10){
//            }
            personnage->avancer();
            qApp->processEvents();
        }

     //tourner a droite
    } else if(movement == 1){
        for(int i = 0; i<90;i++){
            usleep(2000);
            personnage->tourner_droite();
            qApp->processEvents();
        }

     //tourner a gauche
    } else if(movement == 2){

        for(int i = 0; i<90;i++){
            usleep(2000);
            personnage->tourner_gauche();
            qApp->processEvents();
        }
    }
    //se cogner
    else if(movement == 3){

        for(int i = 0; i<plateau->size().height()/25;i++){
            usleep(5000);
            personnage->avancer();
            qApp->processEvents();
        }
        for(int i = 0; i<plateau->size().height()/25;i++){
            usleep(5000);
            personnage->reculer();
            qApp->processEvents();
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
bool Controller::checkAvancer() const
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

bool Controller::checkWin(std::vector<std::vector<Case *>> cases) const
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



