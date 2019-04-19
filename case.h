#ifndef CASE_H
#define CASE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
class Case : public QLabel
{


private:
    bool cristal;
    bool personnage;

    void display();
public:
    Case();
    Case(bool personnage);
    Case(bool personnage, bool cristal);
    ~Case();
    void setPersonnage(bool personnage);
    void setCristal(bool cristal);
    bool havePersonnage();
    bool haveCristal();


};

#endif // CASE_H
