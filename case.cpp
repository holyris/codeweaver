#include "case.h"

Case::Case()
{

}
Case::Case(bool personnage, bool cristal): QLabel()
{
    this->personnage = personnage;
    this->cristal = cristal;
    this->start_personnage = personnage;
    this->start_cristal = cristal;
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

void Case::reset()
{
    personnage = start_personnage;
    cristal = start_cristal;
    this->display();
}

void Case::display()
{

    if(this->havePersonnage()){
        this->setScaledContents( true );
        this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        QPixmap pix("images/personnage.png");
        QTransform transform;
        transform.rotate(personnage_direction*90);
        QPixmap rotatedPixelFrame = pix.transformed(transform);
        this->setPixmap(rotatedPixelFrame);
        this->repaint();
    } else if(this->haveCristal()){
        this->setScaledContents( true );
        this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        this->setPixmap(QPixmap("images/cristal.png"));
        this->repaint();
    } else {
        this->setPixmap(QPixmap());
        this->repaint();
    }
}



bool Case::havePersonnage()
{
    return this->personnage;
}

bool Case::haveCristal()
{
    return this->cristal;
}
