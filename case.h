#ifndef CASE_H
#define CASE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
class Case : public QLabel
{


private:
    bool cristal;
    bool personnage;
    unsigned int personnage_direction;
    bool mur;       // une case reste toujours en mur donc il n'ya pas de start_mur
    bool start_personnage;
    bool start_cristal;
    unsigned int start_personnage_direction;
    void display();

public:
    Case();
    Case(bool personnage, unsigned int personnage_direction, bool cristal, bool mur);

    ~Case();
    void setPersonnage(bool personnage);
    void setCristal(bool cristal);
    void setDirection(unsigned int personnage_direction);
    void reset();
    bool isPersonnage();
    bool isCristal();
    bool isMur();

};

#endif // CASE_H
