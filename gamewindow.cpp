#include "gamewindow.h"

GameWindow::GameWindow() : QWidget()
{

    std::vector<std::vector<Case*>> cases;
    unsigned int lim_x = 10, lim_y = 10;
    Personnage *personnage = new Personnage(9,9,0, lim_x, lim_y);
    Detection *detection = new Detection();

    this->setWindowState(Qt::WindowFullScreen); //  on met en fullscreen

    QGridLayout *grid_main = new QGridLayout();     //  grille principale
    QGridLayout *grid_left = new QGridLayout();     //  grille de gauche pour afficher les fonctions
    QGridLayout *grid_right = new QGridLayout();    //  grille de droite pour afficher le jeu

    QLabel *label = new QLabel();
    label->setScaledContents( true );
    label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    label->setPixmap(QPixmap("image.jpg"));
    grid_main->addWidget(label, 0,1,2,2,0);

    //  rempli cases avec des objets Case, et les ajoute au layout de droite
    for(unsigned int i = 0; i < 10; i++){
        std::vector<Case*> vector;
        for(unsigned int j = 0; j < 10; j++){

            if(i == personnage->getX() && j == personnage->getY()){
                vector.push_back(new Case(true));

                grid_right->addWidget(vector.at(j), i, j);
            }

            else {
                vector.push_back(new Case(false));

                grid_right->addWidget(vector.at(j), i, j);
            }
        }
        cases.push_back(vector);
    }

    this->controller = new Controller(personnage,cases,detection);


    for(unsigned int i = 0; i<10 ; i++){
        grid_left->addWidget(new QLabel("yo"));
    }



    grid_main->addLayout(grid_left, 0,0,1,1,0);
    grid_main->addLayout(grid_right, 0,1,2,2,0);
    this->setLayout(grid_main);



}

GameWindow::~GameWindow()
{

}


//  s'execute quand on appuie sur le clavier
void GameWindow::keyPressEvent(QKeyEvent *event)
{

//    this->controller->keyPressEvent(event);
}
