#ifndef CASE_H
#define CASE_H
#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QTimer>
class Case : public QLabel
{

    Q_OBJECT

private:
    QTimer *timer;
    int currentFrame;
    bool cristal;
    bool personnage;
    unsigned int personnage_direction;
    bool plateforme;       // une case reste toujours en plateforme donc il n'ya pas de start_plateforme
    bool start_personnage;
    bool start_cristal;
    unsigned int start_personnage_direction;
    void display();

public:
    Case();
    ~Case();
    void set(bool personnage, unsigned int personnage_direction, bool cristal, bool plateforme);
    void setPersonnage(bool personnage);
    void setCristal(bool cristal);
    void setDirection(unsigned int personnage_direction);
    void reset();
    void deleteCristal();

    bool isPersonnage() const;
    bool isCristal() const;
    bool isPlateforme() const;

private slots:
    void animation();

};

#endif // CASE_H
