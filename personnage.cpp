#include "personnage.h"

Personnage::Personnage(unsigned int x, unsigned int y,int direction, unsigned int lim_x, unsigned int lim_y)
{
    this->x = x;
    this->y = y;
    this->direction = direction;
    this->lim_x = lim_x;
    this->lim_y = lim_y;
}

Personnage::~Personnage()
{

}


void Personnage::avancer()
{

    //  pour eviter de sortir des limites
        if(this->direction == 0){
            if(y!=0)
                this->y--;
        }
        else if(this->direction == 1){
            if(x!=lim_x-1)
                this->x++;
        }
        else if(this->direction == 2){
            if(y!=lim_y-1)
                this->y++;
        }
        else if (this->direction == 3){
            if(x!=0)
                this->x--;
        }

}

void Personnage::tourner_droite()
{
    if(this->direction == 3)
        direction = 0;
    else direction++;
}


void Personnage::tourner_gauche()
{
    if(this->direction == 0)
        direction = 3;
    else direction --;
}


unsigned int Personnage::getX(){
    return this->x;
}

unsigned int Personnage::getY()
{
    return this->y;
}

