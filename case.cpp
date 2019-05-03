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
}

Case::~Case()
{

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

//  affiche en fonction de l'etat de la case
void Case::display()
{

    if(isPersonnage()){
        this->setScaledContents( true );
        this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        QPixmap pix("images/plateforme+perso.png");
        QTransform transform;
        transform.rotate(personnage_direction*90);
        QPixmap rotatedPixelFrame = pix.transformed(transform);
        this->setPixmap(rotatedPixelFrame);
        this->repaint();
        this->repaint();
    } else if(isCristal()){
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



bool Case::isPersonnage()
{
    return personnage;
}

bool Case::isCristal()
{
    return cristal;
}

bool Case::isPlateforme()
{
    return plateforme;
}
