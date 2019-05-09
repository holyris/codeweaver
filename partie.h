#ifndef PARTIE_H
#define PARTIE_H
#include <QGraphicsView>
#include <fstream>
#include <iostream>
#include <sstream>
#include "personnage.h"
#include "case.h"
#include "cristal.h"
class Partie
{

private:
    int plateforme[8], cristal[8], personnage_start_x, personnage_start_y, personnage_start_direction, last_rand_line;
    int level, number_of_level;
    std::vector<std::vector<Case*> > cases;
    std::vector<Cristal*> cristaux;
    Personnage *personnage;
    QGraphicsView *plateau;
    QGraphicsScene *scene;
    void setCases();


public:
    Partie();
    ~Partie();

    Personnage *getPersonnage() const;
    std::vector<std::vector<Case *> > getCases() const;
    QGraphicsView *getPlateau() const;
    QGraphicsScene *getScene() const;
    std::vector<Cristal *> getCristaux() const;
    int getLevel() const;
    void newPartie();
    void setPersoDirection(int personnage_start_direction);
    void nextLevel();
    void previousLevel();
};

#endif // PARTIE_H
