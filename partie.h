#ifndef PARTIE_H
#define PARTIE_H
#include <fstream>
#include <iostream>
#include <sstream>
#include "personnage.h"
#include "case.h"
class Partie
{

private:
    int plateformes[8], cristaux[8], personnage_start_x, personnage_start_y, personnage_start_direction, last_rand_line;
    std::vector<std::vector<Case*>> cases;
    Personnage* personnage;
public:
    Partie(Personnage* personnage, std::vector<std::vector<Case*>> cases);
    ~Partie();
    void newPartie(std::string difficulty);
    void setCases();
    void setPersonnage();
    void setPlateformes(int plateformes[8]);
    void setCristaux(int cristaux[8]);
    void setPersoX(int personnage_start_x);
    void setPersoY(int personnage_start_y);
    void setPersoDirection(int personnage_start_direction);
};

#endif // PARTIE_H
