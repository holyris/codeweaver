#ifndef PARTIE_H
#define PARTIE_H
#include <QGraphicsView>
#include <fstream>
#include <iostream>
#include <sstream>
#include "personnage.h"
#include "case.h"
class Partie
{

private:
    int plateformes[8], cristaux[8], personnage_start_x, personnage_start_y, personnage_start_direction, last_rand_line;
    int level, number_of_level;
    std::vector<std::vector<Case*>> cases;
    Personnage *personnage;
    QGraphicsView *plateau;
public:
    Partie(Personnage *personnage, std::vector<std::vector<Case*>> cases, QGraphicsView *plateau);
    ~Partie();
    void newPartie();
    void setCases();
    void setPlateformes(int plateformes[8]);
    void setCristaux(int cristaux[8]);
    void setPersoX(int personnage_start_x);
    void setPersoY(int personnage_start_y);
    void setPersoDirection(int personnage_start_direction);
    void nextLevel();
    void previousLevel();
};

#endif // PARTIE_H
