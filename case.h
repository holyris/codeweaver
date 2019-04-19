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
    bool start_personnage;
    bool start_cristal;
    unsigned int personnage_direction;
    void display();

public:
    Case();
    Case(bool personnage, bool cristal);
    ~Case();
    void setPersonnage(bool personnage);
    void setCristal(bool cristal);
    void setDirection(unsigned int personnage_direction);
    void reset();
    bool havePersonnage();
    bool haveCristal();


};

#endif // CASE_H
