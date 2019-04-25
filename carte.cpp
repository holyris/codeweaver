#include "carte.h"

Carte::Carte(int id, cv::Point2f coord)
{

    this->id = id;
    this->type = "none";
    x = coord.x;
    y = coord.y;
    argument_id = -1;
    setName(id);
}

Carte::Carte(int id, cv::Point2f coord, std::string type)
{

    this->id = id;
    this->type = type;
    x = coord.x;
    y = coord.y;
    argument_id = -1;
    setName(id);

}


Carte::Carte(int id, std::string type)
{

    this->id = id;
    this->type = type;
    x = 0;
    y = 0;
    argument_id = -1;
    setName(id);

}

void Carte::setArgumentId(int argument_id)
{
    this->argument_id = argument_id;
    setArgumentName(argument_id);
}

void Carte::setName(int id)
{
    if(id == 16)
        name = QString("Debut");
    else if(id==15)
        name = QString("Fin");
    else if(id==13)
        name = QString("Avancer");
    else if(id==10)
        name = QString("Tourner à gauche");
    else if(id==7)
        name = QString("Tourner à droite");
    else if(id==9)
        name = QString("Debut de Boucle");
    else if(id==8)
        name = QString("Fin de Boucle");
    else if(id==0)
        name = QString("Interagir");

}

void Carte::setArgumentName(int id){
    if(id == 4)
        argument_name = QString("x4");
    else if(id == 14)
        argument_name = QString("x3");
    else if(id == 11)
        argument_name = QString("x2");
    else if(id == 5)
        argument_name = QString("x5");

}
int Carte::getArgumentId()
{
    return this->argument_id;
}



int Carte::getId()
{
    return id;
}

std::string Carte::getType()
{
    return type;
}

int Carte::getX()
{
    return x;
}

int Carte::getY()
{
    return y;
}

QString Carte::getName()
{
    return this->name;
}

QString Carte::getArgumentName()
{
    return this->argument_name;
}

