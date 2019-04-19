#include "case.h"

Case::Case()
{

}
Case::Case(bool personnage){
    this->personnage = personnage;
    this->cristal = false;
    this->display();

}
Case::Case(bool personnage, bool cristal): QLabel()
{
    this->personnage = personnage;
    this->cristal = cristal;

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

void Case::display()
{
    if(this->havePersonnage()){
        this->setScaledContents( true );
        this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        this->setPixmap(QPixmap("images/personnage.png"));
        this->update();
    } else if(this->haveCristal()){
        this->setScaledContents( true );
        this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        this->setPixmap(QPixmap("images/cristal.png"));
        this->update();
    } else {
        this->setPixmap(QPixmap());
        this->update();
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
