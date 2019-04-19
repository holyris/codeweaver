#include "carte.h"

using namespace std;
using namespace cv;

Carte::Carte(int id, cv::Point2f coord)
{

    this->id = id;
    this->type = "none";
    x = coord.x;
    y = coord.y;
    argument_id = -1;

}

Carte::Carte(int id, cv::Point2f coord, std::string type)
{

    this->id = id;
    this->type = type;
    x = coord.x;
    y = coord.y;
    argument_id = -1;

}

void Carte::setArgumentId(int argument_id)
{
    this->argument_id = argument_id;
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


