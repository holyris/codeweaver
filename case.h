#ifndef CASE_H
#define CASE_H
#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPainter>
class Case : public QLabel
{
private:

    int randomRotation, randomMirrorX, randomMirrorY;
    bool plateforme;
    void display();

public:
    Case();
    ~Case();
    void set(bool plateforme);
    void deleteCristal();

    bool isPlateforme() const;
};

#endif // CASE_H
