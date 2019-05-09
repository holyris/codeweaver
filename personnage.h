#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <QObject>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <iostream>

class Personnage: public QGraphicsPixmapItem
{

private:

    // direction : 0=haut, 1=droite, 2=bas, 3=gauche
    unsigned int lim_x, lim_y, start_x, start_y, start_direction;


public:
    Personnage();
    ~Personnage();
    void set(unsigned int x, unsigned int y, int direction);
    void tourner_droite();
    void tourner_gauche();
    void avancer();
    void reculer();
    void reset();



};

#endif // PERSONNAGE_H
