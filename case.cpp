#include "case.h"

Case::Case()
{
    this->personnage = false;
    this->cristal = false;
    this->personnage_direction = 0;
    this->plateforme = false;
    this->start_personnage = 0;
    this->start_cristal = false;
    this->start_personnage_direction = 0;
    this->currentFrame = 0;
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(animation()));

}

Case::~Case()
{
    delete timer;
}
void Case::set(bool personnage, unsigned int personnage_direction, bool cristal, bool plateforme)
{
    this->personnage = personnage;
    this->cristal = cristal;
    this->personnage_direction = personnage_direction;
    this->plateforme = plateforme;
    this->start_personnage = personnage;
    this->start_cristal = cristal;
    this->start_personnage_direction = personnage_direction;
    this->display();
}
void Case::setPersonnage(bool personnage)
{
    this->personnage = personnage;
    this->display();
}

void Case::setCristal(bool cristal)
{
    this->cristal = cristal;
    this->display();
}


void Case::setDirection(unsigned int personnage_direction)
{
    this->personnage_direction = personnage_direction;
    this->display();
}

//  pour revenir a l'etat de debut de partie
void Case::reset()
{
    personnage = start_personnage;
    cristal = start_cristal;
    personnage_direction = start_personnage_direction;
    this->display();
}

void Case::deleteCristal()
{
    if(cristal){
        cristal = false;
        timer->start(150);
        qApp->processEvents();
    }


}

//  affiche en fonction de l'etat de la case
void Case::display()
{
    if(isCristal()){
        this->setScaledContents( true );
        this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        this->setPixmap(QPixmap("images/plateforme+cristal.png"));
        this->repaint();
    } else if(isPlateforme()){
        this->setScaledContents( true );
        this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        this->setPixmap(QPixmap("images/plateforme.png"));
        this->repaint();

    } else {
        this->setPixmap(QPixmap());
        this->repaint();
    }
}



bool Case::isPersonnage() const
{
    return personnage;
}

bool Case::isCristal() const
{
    return cristal;
}

bool Case::isPlateforme() const
{
    return plateforme;
}

void Case::animation()
{
    currentFrame++;
    if(currentFrame==1){
        this->setScaledContents( true );
        this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        this->setPixmap(QPixmap("images/plateforme+explosion1.png"));
        this->repaint();
    }
    else if(currentFrame==2){
        this->setScaledContents( true );
        this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        this->setPixmap(QPixmap("images/plateforme+explosion2.png"));
        this->repaint();
    }
    else if(currentFrame==3){
        this->setScaledContents( true );
        this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        this->setPixmap(QPixmap("images/plateforme+explosion3.png"));
        this->repaint();
    }
    else {
        timer->stop();
        this->display();
    }



}
