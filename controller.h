#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QApplication>
#include <QDesktopWidget>
#include <QObject>
#include <QWidget>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>
#include <QGraphicsView>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/imgproc.hpp>
#include <personnage.h>
#include <case.h>
#include <carte.h>
#include <detection.h>
#include <partie.h>
#include <message.h>

class Controller: QWidget
{
    Q_OBJECT

private:
    int movement;
    Personnage *personnage;
    std::vector<Carte*> cartes;
    std::vector<std::vector<Case*>> cases;
    std::vector<QLabel*> labels;
    Partie *partie;
    Detection *detection;
    QTimer *timer;
    QGraphicsView *plateau;

    void displayFunctions(std::vector<Carte*> cartes);
    unsigned int controlPersonnage(unsigned int loop_begin);
    void movePersonnage(std::string movement);
    void controlKeys(std::vector<Carte*> cartes);
    bool checkAvancer() const;
    bool checkWin(std::vector<std::vector<Case*>> cases) const;
    void resetPlateau();
    inline void CenterWidgets(QWidget *widget, QWidget *host = 0);

public:
    Controller(Personnage *personnage, std::vector<std::vector<Case*>> cases, QGraphicsView *plateau);
    ~Controller();
    void start();
    void setLabels(std::vector<QLabel*> labels);
    void keyPressEvent(QKeyEvent* event);

private slots:
    void controlCartes();
    void animation();

};

#endif // CONTROLLER_H
