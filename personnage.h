#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <QObject>
#include <QWidget>
class Personnage
{

private:

    // direction : 0=haut, 1=droite, 2=bas, 3=gauche
    unsigned int x, y, direction, lim_x, lim_y, start_x, start_y, start_direction;


public:
    Personnage();
    ~Personnage();
    unsigned int getX();
    unsigned int getY();
    unsigned int getDirection();
    void set(unsigned int x, unsigned int y, int direction);

public slots:
    void tourner_droite();
    void tourner_gauche();
    void avancer();
    void interagir();
    void reset();
};

#endif // PERSONNAGE_H
