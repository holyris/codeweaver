#include "gamewindow.h"

GameWindow::GameWindow() : QWidget()
{

    std::vector<std::vector<Case*>> cases;
    unsigned int lim_x = 10, lim_y = 10, personnage_x=5, personnage_y=5, personnage_direction=0;
    Personnage *personnage = new Personnage(personnage_x, personnage_y, personnage_direction,lim_x, lim_y);
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
    for(unsigned int i = 0; i < lim_y; i++){
        std::vector<Case*> vector;
        for(unsigned int j = 0; j < lim_x; j++){

            if(i == personnage->getY() && j == personnage->getX()){
                vector.push_back(new Case(true, false));

                grid_right->addWidget(vector.at(j), i, j);
            }

            else {
                vector.push_back(new Case(false, false));

                grid_right->addWidget(vector.at(j), i, j);
            }
            vector.at(j)->setDirection(personnage_direction);
        }
        cases.push_back(vector);
    }


    std::vector<std::vector<QLabel*>> labels;
    //il est peu probable que le nb de cartes depasse 20
    for(unsigned int i = 0; i<20 ; i++){
        std::vector<QLabel*> vector;
        for(unsigned int j = 0; j<2 ; j++){
            vector.push_back(new QLabel(""));
            grid_left->addWidget(vector.at(j),i,j);
        }
        labels.push_back(vector);
    }


    this->controller = new Controller(personnage,cases,detection);
    this->controller->setLabels(labels);



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
    controller->controlCartes();
//    this->controller->keyPressEvent(event);
}
