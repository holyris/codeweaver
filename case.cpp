#include "case.h"

Case::Case()
{
    this->plateforme = false;
    randomRotation = 0;
}

Case::~Case()
{
}
void Case::set(bool plateforme)
{

    this->plateforme = plateforme;

    randomRotation = rand() % 4;
    randomMirrorX = rand() % 2;
    randomMirrorY = rand() % 2;

    if(randomMirrorX==0) randomMirrorX = -1;
    if(randomMirrorY==0) randomMirrorY = -1;
    this->display();
}

//  affiche en fonction de l'etat de la case
void Case::display()
{
    this->setScaledContents( true );
    this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    QPixmap pix;

    if(isPlateforme()){
        pix.load("images/plateforme.png");
    }

    pix = pix.transformed(QTransform().rotate(randomRotation*90));
    pix = pix.transformed(QTransform().scale(randomMirrorX, randomMirrorY));
    this->setPixmap(pix);
    this->repaint();
}

bool Case::isPlateforme() const
{
    return plateforme;
}


