#include "case.h"

Case::Case()
{

}
Case::Case(bool personnage, unsigned int personnage_direction, bool cristal, bool mur): QLabel()
{
    this->personnage = personnage;
    this->cristal = cristal;
    this->personnage_direction = personnage_direction;
    this->mur = mur;
    this->start_personnage = personnage;
    this->start_cristal = cristal;
    this->start_personnage_direction = personnage_direction;
    this->display();

}

Case::~Case()
{

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
    if(this->isPersonnage()){
        this->setScaledContents( true );
        this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        QPixmap pix("images/personnage.png");
        QTransform transform;
        transform.rotate(personnage_direction*90);
        QPixmap rotatedPixelFrame = pix.transformed(transform);
        this->setPixmap(rotatedPixelFrame);
        this->repaint();
    } else if(this->isCristal()){
        this->setScaledContents( true );
        this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        this->setPixmap(QPixmap("images/cristal.png"));
        this->repaint();
    } else {
        this->setPixmap(QPixmap());
        this->repaint();
    }
}



bool Case::isPersonnage()
{
    return this->personnage;
}

bool Case::isCristal()
{
    return this->cristal;
}
