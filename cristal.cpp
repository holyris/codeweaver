#include "cristal.h"

Cristal::Cristal(): QGraphicsPixmapItem(QPixmap("images/cristal.png"))
{
    this->setZValue(10);
    this->setTransformOriginPoint(this->boundingRect().center());
    this->setOffset(-5,-5);
}

Cristal::~Cristal()
{

}

void Cristal::set(unsigned int x, unsigned int y)
{
    this->setPos(x,y);

}

void Cristal::destroy()
{
    this->hide();
}

void Cristal::reset()
{
    if(!this->isVisible())
        this->show();
}
