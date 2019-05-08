#include "personnage.h"


Personnage::Personnage(QPixmap &pixmap): QGraphicsPixmapItem(pixmap)
{
//    this->setTransformOriginPoint(this->boundingRect().center());

//    this->setOffset(this->transformOriginPoint());
    this->setTransformOriginPoint(this->boundingRect().center());

}

Personnage::~Personnage()
{

}
void Personnage::avancer()
{
        //avance en haut
        if(this->rotation() == 0)
            this->moveBy(0,-1);

        //avance a droite
        else if(this->rotation() == 90)
            this->moveBy(1,0);



        //avance en bas
        else if(this->rotation() == 180)
            this->moveBy(0,1);

        //avance a gauche
        else if (this->rotation() == 270)
            this->moveBy(-1,0);



}

void Personnage::reculer()
{

        //recule vers le bas
        if(this->rotation() == 0)
            this->moveBy(0,1);

        //recule vers la gauche
        else if(this->rotation() == 90)
            this->moveBy(-1,0);


        //recule vers le haut
        else if(this->rotation() == 180)
            this->moveBy(0,-1);

        //recule vers la droite
        else if (this->rotation() == 270)
            this->moveBy(1,0);



}


void Personnage::tourner_droite()
{
    if(this->rotation() == 360)
        this->setRotation(0);

    this->setRotation(this->rotation()+1);
    if(this->rotation() == 360)
        this->setRotation(0);

}


void Personnage::tourner_gauche()
{
    if(this->rotation() == 0)
        this->setRotation(360);
    this->setRotation(this->rotation()-1);
    if(this->rotation() == 360)
        this->setRotation(0);

}

void Personnage::set(unsigned int x, unsigned int y, int direction)
{
        this->setPos(x,y);
        this->setRotation(direction);
        this->start_x = x;
        this->start_y = y;
        this->start_direction = direction;
}


void Personnage::reset()
{
    this->setPos(start_x,start_y);
    this->setRotation(start_direction);
}



