#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <QObject>
#include <QWidget>
class Personnage
{

private:

    // direction : 0=haut, 1=droite, 2=bas, 3=gauche
    unsigned int x, y, direction, lim_x, lim_y;


public:
    Personnage(unsigned int x, unsigned int y, int direction, unsigned int lim_x, unsigned int lim_y);
    ~Personnage();
    unsigned int getX();
    unsigned int getY();

public slots:

    void tourner_droite();
    void tourner_gauche();
    void avancer();
    void interagir();
};

#endif // PERSONNAGE_H
